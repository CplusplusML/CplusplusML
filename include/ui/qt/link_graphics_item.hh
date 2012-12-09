#ifndef         _CPLUSPLUSML_UI_QT_LINK_GRAPHICS_ITEM_HH_
# define        _CPLUSPLUSML_UI_QT_LINK_GRAPHICS_ITEM_HH_

# include <QGraphicsItem>
# include <QPen>

# include "object/link.hh"

namespace CplusplusML
{
  namespace Ui
  {
    namespace Qt
    {
      namespace Object = ::CplusplusML::Object;

      class LinkConnection;

      class Link : public QGraphicsObject
      {
        Q_OBJECT

      public:
        Link(Object::Link* linkObject);

        virtual ~Link() { }

        void Render(void);

        void adjustHandles();
        void disableHandles();
        void enableHandles();

        void adjustConnections();
        void adjustLinkTip();

        QVariant itemChange(GraphicsItemChange change, const QVariant &value);

        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget);
        QPainterPath shape() const;
        QRectF boundingRect() const;

        //DEBUG
        bool sceneEvent(QEvent *event);
        bool eventFilter(QObject* obj, QEvent *event);
        //    bool sceneEventFilter(QObject *obj, QEvent *ev);

      public slots:
        void itemMoved();

      protected:
        enum class LinkOrientation
        {
          Horizontal,
          Vertical
        };

        template <class T>
        T* searchSceneItem(QPointF const& pos);

        void    adjustLink();

      private:
        QPen        pen;
        QPen        outlinePen;
        QPointF     tail;
        QPointF     head;
        LinkOrientation orientation;
        QGraphicsObject* tailItem;
        QGraphicsObject* headItem;
        QPolygonF   arrowHead;

        //    GrabHandle*  handles[2];

        QList<LinkConnection*> connections;
      };
    }
  }
}

#endif  //!_CPLUSPLUSML_UI_QT_LINK_GRAPHICS_ITEM_HH_
