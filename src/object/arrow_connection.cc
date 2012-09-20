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
  bool eventHandled = QGraphicsObject::sceneEvent(event);
  return eventHandled;
}

QVariant Object::ArrowConnection::itemChange(GraphicsItemChange change, const QVariant &value)
{
  if (change == QGraphicsItem::ItemScenePositionHasChanged)
    {
      //     qDebug() << "CONNECTION - POSITION CHANGED";
      emit moved(this);
    }
  return QGraphicsObject::itemChange(change, value);
}

void Object::ArrowConnection::paint(QPainter *painter,
                                    const QStyleOptionGraphicsItem *,
                                    QWidget *)
{
  painter->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);

  {
    QPen _pen;
    _pen.setCapStyle(Qt::FlatCap);
    _pen.setWidth(1);
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
  //  qDebug() << "CONNECTION - MOVECENTER";
  emit moved(this);
}
