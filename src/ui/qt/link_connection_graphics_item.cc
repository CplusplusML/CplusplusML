#include <QPainter>

#include "ui/qt/link_connection_graphics_item.hh"

namespace CplusplusML
{
  namespace Ui
  {
    namespace Qt
    {
      LinkConnection::LinkConnection(QGraphicsItem* parent, int size) :
        QGraphicsObject(parent)
      {
        setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
        rect.setRect(0, 0, size, size);
      }

      bool LinkConnection::sceneEvent(QEvent* event)
      {
        bool eventHandled = QGraphicsObject::sceneEvent(event);
        return eventHandled;
      }

      QVariant LinkConnection::itemChange(GraphicsItemChange change, const QVariant &value)
      {
        if (change == QGraphicsItem::ItemScenePositionHasChanged)
          {
            //     qDebug() << "CONNECTION - POSITION CHANGED";
            emit moved(this);
          }
        return QGraphicsObject::itemChange(change, value);
      }

      void LinkConnection::paint(QPainter *painter,
                                          const QStyleOptionGraphicsItem *,
                                          QWidget *)
      {
        painter->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);

        {
          QPen _pen;
          _pen.setCapStyle(::Qt::FlatCap);
          _pen.setWidth(1);
          _pen.setBrush(::Qt::blue);
          painter->setPen(_pen);
        }
        painter->drawLine(rect.bottomLeft(), rect.topRight());
        painter->drawLine(rect.topLeft(), rect.bottomRight());
      }

      QRectF LinkConnection::boundingRect() const
      {
        return (rect);
      }

      QPointF LinkConnection::center() const
      {
        return (rect.center());
      }

      void LinkConnection::moveCenter(QPointF const& center)
      {
        prepareGeometryChange();
        rect.moveCenter(center);
        //  qDebug() << "CONNECTION - MOVECENTER";
        emit moved(this);
      }
    }
  }
}
