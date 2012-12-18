#ifndef         _CPLUSPLUSML_UI_QT_LINK_GRAPHICS_ITEM_HH_
# define        _CPLUSPLUSML_UI_QT_LINK_GRAPHICS_ITEM_HH_

# include <QGraphicsItem>
# include <QPen>

# include "object/link.hh"
# include "ui/qt/link_head_graphics_item.hh"

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

        void keyReleaseEvent(QKeyEvent* event);

        template <class T>
        T* searchSceneItem(QPointF const& pos);

        void    adjustLink();

        QLineF firstPathLine();
        QLineF lastPathLine();
        double angle();

        LinkHead frontHead;
        LinkHead backHead;
        QPen     pen;

      private:
        bool            hovered;
        Object::Link*   object;
        QPen            outlinePen;
        QPainterPath    path;
        LinkOrientation orientation;
        QGraphicsObject* tailItem;
        QGraphicsObject* headItem;
        QPolygonF   arrowHead;
      };
    }
  }
}

#endif  //!_CPLUSPLUSML_UI_QT_LINK_GRAPHICS_ITEM_HH_
