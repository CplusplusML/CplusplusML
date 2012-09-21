// DEBUG
#include <QDebug>
#include <iostream>
//

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include "object/arrow.hh"

Object::GrabHandle::GrabHandle(QGraphicsItem* parent, QPointF* boundPoint) :
  QGraphicsRectItem(parent), boundPoint(boundPoint), currentConnection(0)
{
  setRect(0, 0, 6, 6);
  setBrush(Qt::green);
  setZValue(2.0);
  moveCenter(*boundPoint);
}

void Object::GrabHandle::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *option,
                               QWidget *widget)
{
  //  qDebug() << "GRAB_HANDLE PAINT";
  QGraphicsRectItem::paint(painter, option, widget);

  {
    QPen _pen;
    _pen.setStyle(Qt::SolidLine);
    _pen.setWidth(0);
    _pen.setBrush(Qt::black);
    painter->setPen(_pen);
    painter->drawLine(rect().bottomLeft(), rect().topRight());
    painter->drawLine(rect().topLeft(), rect().bottomRight());
  }
}

void    Object::GrabHandle::moveCenter(QPointF const& center)
{
  if (rect().center() == center)
    return;

  QRectF newRect = rect();

  newRect.moveCenter(center);
  prepareGeometryChange();
  setRect(newRect);
  emit moved(rect().center(), boundPoint);
}

Object::ArrowConnection* Object::GrabHandle::searchConnection(QPointF const& point)
{
  QList<QGraphicsItem*> hoveredItems = scene()->items(point);

  hoveredItems.removeAll(this);
  foreach(QGraphicsItem* item, hoveredItems)
    {
      ArrowConnection* conn = dynamic_cast<ArrowConnection*>(item);

      if (conn)
        return conn;
    }
  return 0;
}

void Object::GrabHandle::connectionMoved(ArrowConnection* connection)
{
  moveCenter(mapFromItem(connection, connection->center()));
}

bool Object::GrabHandle::sceneEvent(QEvent *event)
{
  //  qDebug() << "GRAB HANDLE - EVENT: " << event;
  if (event->type() == QEvent::GraphicsSceneMousePress)
    {
      if (currentConnection)
        disconnect(currentConnection, SIGNAL(moved(ArrowConnection*)),
                   this, SLOT(connectionMoved(ArrowConnection*)));
      currentConnection = 0;
    }
  else if (event->type() == QEvent::GraphicsSceneMouseRelease)
    {
      QGraphicsSceneMouseEvent *me = static_cast<QGraphicsSceneMouseEvent*>(event);
      ArrowConnection* connection = searchConnection(me->scenePos());

      if (connection != 0)
        {
          currentConnection = connection;
          connect(connection, SIGNAL(moved(ArrowConnection*)),
                  this, SLOT(connectionMoved(ArrowConnection*)));
        }
    }
  else if (event->type() == QEvent::GraphicsSceneMouseMove)
    {
      QGraphicsSceneMouseEvent *me = static_cast<QGraphicsSceneMouseEvent*>(event);
      QPointF cursorPos = me->pos();
      ArrowConnection* connection = searchConnection(me->scenePos());

      if (connection != 0)
        cursorPos = mapFromItem(connection, connection->center());

      moveCenter(cursorPos);
    }
  else
    return false;
  return true;
}

Object::Arrow_::Arrow_()
{
  Render();
}

void Object::Arrow_::Render(void)
{
  setFlag(QGraphicsItem::ItemIsMovable, true);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
  setZValue(1.0);

  pen.setStyle(Qt::DashDotLine);
  pen.setWidth(2);
  pen.setBrush(Qt::black);
  pen.setCapStyle(Qt::FlatCap);
  pen.setJoinStyle(Qt::RoundJoin);

  outlinePen.setStyle(Qt::SolidLine);
  outlinePen.setCapStyle(Qt::RoundCap);
  outlinePen.setJoinStyle(Qt::RoundJoin);
  outlinePen.setWidth(pen.width());
  outlinePen.setBrush(Qt::green);

  prepareGeometryChange();
  tail = QPointF(0, 0);
  head = QPointF(200, 200);
  handles[0] = new GrabHandle(this, &tail);
  handles[1] = new GrabHandle(this, &head);
  connect(handles[0], SIGNAL(moved(QPointF, QPointF*)),
          this, SLOT(onGrabHandleMove(QPointF, QPointF*)));
  connect(handles[1], SIGNAL(moved(QPointF, QPointF*)),
          this, SLOT(onGrabHandleMove(QPointF, QPointF*)));
  disableHandles();

  connections << new ArrowConnection(this);
  connections << new ArrowConnection(this);
  adjustConnections();
  adjustArrowTip();

  //DEBUG
  QCoreApplication::instance()->installEventFilter(this);
}

void Object::Arrow_::disableHandles()
{
  setZValue(1.0);
  handles[0]->hide();
  handles[1]->hide();
}

void Object::Arrow_::enableHandles()
{
  setZValue(2.0);
  handles[0]->show();
  handles[1]->show();
}

void Object::Arrow_::adjustConnections()
{
  int numSegments = connections.size() + 1;
  qreal increment = 1.0 / numSegments;
  qreal currentPos = increment;
  QLineF line = QLineF(tail, head);

  prepareGeometryChange();
  foreach(ArrowConnection* connection, connections)
    {
      connection->moveCenter(line.pointAt(currentPos));
      currentPos += increment;
    }
}

QVariant Object::Arrow_::itemChange(GraphicsItemChange change, const QVariant &value)
{
  //  qDebug() << "ITEM CHANGE";
  if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
      bool selected = value.toBool();

      if (selected)
        enableHandles();
      else
        disableHandles();
    }
  return QGraphicsObject::itemChange(change, value);
}

void Object::Arrow_::adjustArrowTip()
{
  const double Pi = std::atan(1.0) * 4;
  qreal arrowSize = 20.0;
  QLineF arrowLine(tail, head);
  double angle = ::acos(arrowLine.dx() / arrowLine.length());

  if (arrowLine.dy() >= 0)
    angle = Pi - angle;
  else
    angle = angle - Pi;

  QPointF arrowP1 = head + QPointF(sin(angle + Pi / 3) * arrowSize,
                                   cos(angle + Pi / 3) * arrowSize);
  QPointF arrowP2 = head + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                   cos(angle + Pi - Pi / 3) * arrowSize);

  arrowHead.clear();
  arrowHead << head << arrowP1 << arrowP2 << head;
}

void Object::Arrow_::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem */*option*/,
                           QWidget */*widget*/)
{
  painter->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);

  if (true) // When hovered
    {
      painter->setPen(outlinePen);
      painter->drawPath(shape());
    }
  painter->setPen(pen);
  painter->drawLine(QLineF(tail, head));
  painter->drawPolygon(arrowHead);
  if (true) // When debugging =D
    {
      QPen _pen;
      _pen.setStyle(Qt::DotLine);
      _pen.setWidth(0);
      _pen.setBrush(Qt::magenta);
      painter->setPen(_pen);
      painter->drawRect(boundingRect());
    }
  if (false) // When debugging =D
    {
      QRectF prect(0, 0, 20, 20);
      QPen _pen;
      _pen.setStyle(Qt::SolidLine);
      _pen.setWidth(2);
      _pen.setBrush(Qt::red);
      painter->setPen(_pen);
      prect.moveCenter(head);
      painter->drawRect(prect);

      _pen.setBrush(Qt::blue);
      painter->setPen(_pen);
      prect.moveCenter(tail);
      painter->drawRect(prect);
    }
}

QPainterPath Object::Arrow_::shape() const
{
  QPainterPathStroker stroker;
  QPainterPath path;

  path.moveTo(tail);
  path.lineTo(head);
  path.addPolygon(arrowHead);
  stroker.setWidth(pen.width() * 2);
  stroker.setCapStyle(Qt::RoundCap);
  stroker.setJoinStyle(Qt::RoundJoin);
  return stroker.createStroke(path);
}

QRectF Object::Arrow_::boundingRect() const
{
  // qreal extra = (pen.width() + 20.0) / 2.0;

  // return (QRectF(tail, head).normalized().adjusted(-extra, -extra, extra, extra) |
  //         childrenBoundingRect());

  // Not really optimized, but good enough for now
  return (shape().boundingRect());
}

void        Object::Arrow_::onGrabHandleMove(QPointF const& newPos, QPointF* boundPoint)
{
  if (*boundPoint == newPos)
    return;
  prepareGeometryChange();
  //  QPointF bkp = *boundPoint;
  *boundPoint = newPos;
  //  QLineF        line(tail, head);
  adjustConnections();
  adjustArrowTip();
}

//DEBUG
bool Object::Arrow_::sceneEvent(QEvent *ev)
{
  //  qDebug() << "SCENE EVENT: " << ev;
  return QGraphicsObject::sceneEvent(ev);
}

bool Object::Arrow_::eventFilter(QObject *obj, QEvent *ev)
{
  //  qDebug() << "GLOBAL EVENT: " << ev << " - OBJ: " << obj;
  return QObject::eventFilter(obj, ev);
}
