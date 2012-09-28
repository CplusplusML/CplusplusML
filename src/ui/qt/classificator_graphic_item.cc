#include        <QPainter>

#include        "ui/qt/classificator_graphic_item.hh"

namespace                       CplusplusML
{
  namespace                     Ui
  {
    namespace                   Qt
    {
      QRectF                    Classificator::boundingRect() const
      {
        qreal                   penWidth = 1;

        return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                      20 + penWidth, 20 + penWidth);
      }

      void                      Classificator::paint(QPainter *painter,
                                                     const QStyleOptionGraphicsItem *,
                                                     QWidget *)
      {
        painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);
      }
    }
  }
}
