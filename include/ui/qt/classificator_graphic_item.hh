#ifndef         _CPLUSPLUSML_UI_QT_CLASSIFICATOR_U_GRAPHIC_U_ITEM_HH_
# define        _CPLUSPLUSML_UI_QT_CLASSIFICATOR_U_GRAPHIC_U_ITEM_HH_

# include       <QGraphicsItem>

# include       "object/classificator.hh"

namespace               CplusplusML
{
  namespace             Ui
  {
    namespace           Qt
    {
      namespace         Object = ::CplusplusML::Object;

      class             Classificator: public QGraphicsItem
      {
      public:
        Classificator(Object::Classificator *object = 0,
                      QGraphicsItem *parent = 0):
          QGraphicsItem(parent),
          object_(object)
        {
        }

        Classificator(QGraphicsItem *parent = 0):
          QGraphicsItem(parent),
          object_(NULL)
        {
        }

        QRectF          boundingRect() const;
        void            paint(QPainter *painter,
                              const QStyleOptionGraphicsItem *option,
                              QWidget *widget);

        inline Object::Classificator    *GetObject(void) const {
          return object_;
        }

      protected:
        Object::Classificator   *object_;
      };
    }
  }
}

#endif          // _CPLUSPLUSML_UI_QT_CLASSIFICATOR_U_GRAPHIC_U_ITEM_HH_
