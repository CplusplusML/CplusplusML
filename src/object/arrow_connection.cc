#include <QDebug>

#include <QPainter>

#include "object/arrow_connection.hh"

Object::ArrowConnection::ArrowConnection(QGraphicsItem* parent, int size) :
  QGraphicsObject(parent)
{
  setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
  rect.setRect(0, 0, size, size);
}

bool Object::ArrowConnection::sceneEvent(QEvent* event)
{
  qDebug() << "ArrowConnection::EVENT: " << event;
  bool eventHandled = false;

  // if (event->type() == QEvent::GraphicsSceneMousePress)
  //   {
  //     eventHandled = true;
  //   }
  // else if (event->type() == QEvent::GraphicsSceneMouseRelease)
  //   {
  //     QGraphicsSceneMouseEvent *me = static_cast<QGraphicsSceneMouseEvent*>(event);
  //     ArrowConnection* connection = searchConnection(me->scenePos());

  //     if (connection != 0)
  //       {
  //         QPointF* connectedPoint = 0;

  //         if (pressedHandle == handles[0])
  //           connectedPoint = &tail;
  //         else if (pressedHandle == handles[1])
  //           connectedPoint = &head;
  //         else
  //           Q_ASSERT(false);
  //         pointLookup.insert(connection, connectedPoint);
  //         connect(connection, SIGNAL(moved(ArrowConnection*)),
  //                 this, SLOT(connectionMoved(ArrowConnection*)));
  //       }
  //     pressedHandle = 0;

  //     eventHandled = true;
  //   }
  // else if (event->type() == QEvent::GraphicsSceneMouseMove)
  //   {
  //     QGraphicsSceneMouseEvent *me = static_cast<QGraphicsSceneMouseEvent*>(event);
  //     QPointF cursorPos = mapFromItem(watched, me->pos());

  //     ArrowConnection* connection = searchConnection(me->scenePos());

  //     if (connection != 0)
  //       cursorPos = mapFromItem(connection, connection->center());

  //     prepareGeometryChange();
  //     if (watched == handles[0])
  //       tail = cursorPos;
  //     else if (watched == handles[1])
  //       head = cursorPos;
  //     adjustHandles();
  //     adjustConnections();

  //     eventHandled = true;
  //   }
  // else
  eventHandled = QGraphicsObject::sceneEvent(event);
  return eventHandled;
}

QVariant Object::ArrowConnection::itemChange(GraphicsItemChange change, const QVariant &value)
{
  if (change == QGraphicsItem::ItemScenePositionHasChanged)
    {
      emit moved(this);
    }
  return QGraphicsObject::itemChange(change, value);
}

void Object::ArrowConnection::paint(QPainter *painter,
                                    const QStyleOptionGraphicsItem *,
                                    QWidget *)
{
  {
    QPen _pen;
    _pen.setCapStyle(Qt::FlatCap);
    _pen.setWidth(3);
    _pen.setBrush(Qt::blue);
    painter->setPen(_pen);
  }
  painter->drawLine(rect.bottomLeft(), rect.topRight());
  painter->drawLine(rect.topLeft(), rect.bottomRight());
}

QRectF Object::ArrowConnection::boundingRect() const
{
  return (rect);
}

QPointF Object::ArrowConnection::center() const
{
  return (rect.center());
}

void Object::ArrowConnection::moveCenter(QPointF const& center)
{
  prepareGeometryChange();
  rect.moveCenter(center);
  emit moved(this);
}
