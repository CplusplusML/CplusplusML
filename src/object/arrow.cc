// DEBUG
#include <QDebug>
#include <iostream>
//

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include "object/arrow.hh"

Object::GrabHandle::GrabHandle(QGraphicsItem* parent) : QGraphicsRectItem(parent)
{
  setRect(0, 0, 6, 6);
  setBrush(Qt::green);
}

void Object::GrabHandle::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *option,
                               QWidget *widget)
{
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
  QRectF newRect = rect();

  newRect.moveCenter(center);
  setRect(newRect);
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
  handles[0] = new GrabHandle(this);
  handles[1] = new GrabHandle(this);
  disableHandles();
  adjustHandles();

  connections << new ArrowConnection(this);
  connections << new ArrowConnection(this);
  adjustConnections();
}

void Object::Arrow_::disableHandles()
{
  // Hack to put grabHandle children on top of ArrowConnections
  setZValue(1.0);
  handles[0]->hide();
  handles[1]->hide();
}

void Object::Arrow_::enableHandles()
{
  // see above
  setZValue(2.0);
  handles[0]->show();
  handles[1]->show();
}

void Object::Arrow_::adjustHandles()
{
  handles[0]->moveCenter(tail);
  handles[1]->moveCenter(head);
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
  if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
      bool selected = value.toBool();

      if (selected)
        enableHandles();
      else
        disableHandles();
    }
  else if (change == QGraphicsItem::ItemSceneHasChanged)
    {
      handles[0]->installSceneEventFilter(this);
      handles[1]->installSceneEventFilter(this);
    }
  return QGraphicsObject::itemChange(change, value);
}

void Object::Arrow_::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem */*option*/,
                           QWidget */*widget*/)
{
  painter->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);

  painter->setPen(pen);
  painter->drawLine(QLineF(tail, head));

  // Arrow head
  {
    // QPen _pen;
    // _pen.setStyle(Qt::SolidLine);
    // _pen.setWidth(pen.width());
    // _pen.setBrush(Qt::magenta);
    // painter->setPen(_pen);

    const double Pi = std::atan(1.0) * 4;
    qreal arrowSize = 20.0;
    QLineF arrowLine(tail, head);
    double angle = ::acos(arrowLine.dx() / arrowLine.length());
    if (arrowLine.dy() >= 0)
      angle = (Pi * 2) - angle;

    QPointF arrowP1 = tail + QPointF(sin(angle + Pi / 3) * arrowSize,
                                               cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = tail + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                               cos(angle + Pi - Pi / 3) * arrowSize);

    arrowHead.clear();
    arrowHead << tail << arrowP1 << arrowP2 << tail;
    painter->drawPolygon(arrowHead);
  }
  if (false) // When hovered
    {
      painter->setPen(outlinePen);
      painter->drawPath(shape());
    }

  if (false) // When debugging =D
    {
      QPen _pen;
      _pen.setStyle(Qt::DotLine);
      _pen.setWidth(0);
      _pen.setBrush(Qt::magenta);
      painter->setPen(_pen);
      painter->drawRect(boundingRect());
    }
}

QPainterPath Object::Arrow_::shape() const
{
  QPainterPathStroker stroker;
  QPainterPath path;

  path.moveTo(tail);
  path.lineTo(head);
  //path.moveTo(head);
  path.addPolygon(arrowHead);
  stroker.setWidth(pen.width());
  stroker.setCapStyle(Qt::RoundCap);
  stroker.setJoinStyle(Qt::RoundJoin);
  return stroker.createStroke(path);
}

Object::ArrowConnection* Object::Arrow_::searchConnection(QPointF const& point)
{
  QList<QGraphicsItem*> hoveredItems = scene()->items(point);
  QList<QGraphicsItem*> ignoredItems = childItems() << this;

  foreach(QGraphicsItem* item, ignoredItems)
    hoveredItems.removeAll(item);

  foreach(QGraphicsItem* item, hoveredItems)
    {
      ArrowConnection* conn = dynamic_cast<ArrowConnection*>(item);

      if (conn)
        return conn;
    }
  return 0;
}

bool Object::Arrow_::sceneEvent(QEvent* event)
{
  return QGraphicsObject::sceneEvent(event);
}

bool Object::Arrow_::sceneEventFilter(QGraphicsItem *watched,
                                      QEvent *event)
{
  //  qDebug() << "FILTERED EVENT: " << event;
  if (event->type() == QEvent::GraphicsSceneMousePress)
    {
      pressedHandle = dynamic_cast<GrabHandle*>(watched);
      Q_ASSERT(pressedHandle);
    }
  else if (event->type() == QEvent::GraphicsSceneMouseRelease)
    {
      QGraphicsSceneMouseEvent *me = static_cast<QGraphicsSceneMouseEvent*>(event);
      ArrowConnection* connection = searchConnection(me->scenePos());

      if (connection != 0)
        {
          QPointF* connectedPoint = 0;

          if (pressedHandle == handles[0])
            connectedPoint = &tail;
          else if (pressedHandle == handles[1])
            connectedPoint = &head;
          else
            Q_ASSERT(false);
          pointLookup.insert(connection, connectedPoint);
          connect(connection, SIGNAL(moved(ArrowConnection*)),
                  this, SLOT(connectionMoved(ArrowConnection*)));
        }
      pressedHandle = 0;
    }
  else if (event->type() == QEvent::GraphicsSceneMouseMove)
    {
      QGraphicsSceneMouseEvent *me = static_cast<QGraphicsSceneMouseEvent*>(event);
      QPointF cursorPos = mapFromItem(watched, me->pos());

      ArrowConnection* connection = searchConnection(me->scenePos());

      if (connection != 0)
        cursorPos = mapFromItem(connection, connection->center());

      prepareGeometryChange();
      if (watched == handles[0])
        tail = cursorPos;
      else if (watched == handles[1])
        head = cursorPos;
      adjustHandles();
      adjustConnections();
    }
  else
    return false;
  return true;
}

QRectF Object::Arrow_::boundingRect() const
{
  qreal extra = (pen.width() + 20.0) / 2.0;

  return (QRectF(tail, head).normalized().adjusted(-extra, -extra, extra, extra) |
          childrenBoundingRect());
  // return (QRectF(tail, head) |
  //         childrenBoundingRect());
}

void Object::Arrow_::connectionMoved(ArrowConnection* connection)
{
  prepareGeometryChange();
  auto iterator = pointLookup.find(connection);

  Q_ASSERT(iterator != pointLookup.end());
  QPointF* point = iterator.value();
  // qDebug() << "this->pos()" << this->pos();
  // qDebug() << "connection->pos()" << connection->pos();
  // qDebug() << "conn->center(): " << connection->center();
  // qDebug() << "conn->center().mapped(): " << mapFromItem(connection, connection->center());
  // qDebug() << "scene(): " << scene();
  // qDebug() << "parentItem(): " << parentItem();
  *point = mapFromItem(connection, connection->center());
  adjustConnections();
  adjustHandles();
}
