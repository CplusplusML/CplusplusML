#ifndef         _CPLUSPLUSML_UI_QT_LINK_CONNECTION_GRAPHICS_ITEM_HH_
# define        _CPLUSPLUSML_UI_QT_LINK_CONNECTION_GRAPHICS_ITEM_HH_

#include <QGraphicsObject>

namespace CplusplusML
{
  namespace Ui
  {
    namespace Qt
    {
      class LinkConnection : public QGraphicsObject
      {
        Q_OBJECT

      public:
        LinkConnection(QGraphicsItem* parent, int size = 6);

        bool sceneEvent(QEvent* event);
        QVariant itemChange(GraphicsItemChange change, const QVariant &value);
        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget);
        virtual QRectF boundingRect() const;

        QPointF center() const;
        void moveCenter(QPointF const& center);

      signals:
        void moved(LinkConnection*);
        void hovered(LinkConnection*);

      private:
        QRectF              rect;
      };
    }
  }
}

#endif  // !_CPLUSPLUSML_UI_QT_LINK_CONNECTION_GRAPHICS_ITEM_HH_
