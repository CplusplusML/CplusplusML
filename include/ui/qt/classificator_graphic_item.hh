#ifndef         _CPLUSPLUSML_UI_QT_CLASSIFICATOR_U_GRAPHIC_U_ITEM_HH_
# define        _CPLUSPLUSML_UI_QT_CLASSIFICATOR_U_GRAPHIC_U_ITEM_HH_

# include       <QGraphicsItem>

# include       "object/classificator.hh"
# include       "ui/qt/diagram_graphics_item.hh"

namespace               CplusplusML
{
  namespace             Ui
  {
    namespace           Qt
    {
      namespace         Object = ::CplusplusML::Object;

      class             Classificator: public DiagramGraphicsItem
      {
        Q_OBJECT

      public:
        Classificator(Object::Classificator *object = 0,
                      QGraphicsItem *parent = 0):
          DiagramGraphicsItem(parent),
          object_(object)
        {
          this->setZValue(1.0);
          this->setFlag(QGraphicsItem::ItemIsSelectable, true);
          this->setFlag(QGraphicsItem::ItemIsFocusable, true);
        }

        Classificator(QGraphicsItem *parent = 0):
          DiagramGraphicsItem(parent),
          object_(NULL)
        {
        }

        QRectF          boundingRect() const;
        void            paint(QPainter *painter,
                              const QStyleOptionGraphicsItem *option,
                              QWidget *widget);
        void      mouseMoveEvent(QGraphicsSceneMouseEvent* event);

        inline Object::Classificator    *GetObject(void) const {
          return object_;
        }

      signals:
        void moved();

      protected:
        Object::Classificator   *object_;
      };
    }
  }
}

#endif          // _CPLUSPLUSML_UI_QT_CLASSIFICATOR_U_GRAPHIC_U_ITEM_HH_
