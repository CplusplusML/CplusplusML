#ifndef         _CPLUSPLUSML_UI_QT_DIAGRAM_GRAPHICS_ITEM_HH_
# define        _CPLUSPLUSML_UI_QT_DIAGRAM_GRAPHICS_ITEM_HH_

#include <QGraphicsObject>

namespace CplusplusML
{
  namespace Ui
  {
    namespace Qt
    {
      class DiagramGraphicsItem : public QGraphicsObject
      {
        Q_OBJECT

      public:
        DiagramGraphicsItem();
        DiagramGraphicsItem(QGraphicsItem* parent);
        ~DiagramGraphicsItem();

        void keyReleaseEvent(QKeyEvent* event);

      signals:
        void    removed();
      };
    }
  }
}

#endif  //!_CPLUSPLUSML_UI_QT_DIAGRAM_GRAPHICS_ITEM_HH_
