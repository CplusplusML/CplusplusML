#ifndef _CPLUSPLUSML_UI_DIAGRAM_SCENE_H
# define _CPLUSPLUSML_UI_DIAGRAM_SCENE_H

# include <QGraphicsScene>

# include "diagram_item.h"

namespace                 cplusplusml {
  namespace               ui {

    /*
      The scene containing all graphic elements and handling events.
    */
    class                 DiagramScene: public QGraphicsScene
    {
    public:
      enum      Mode {
        mode_select,
        mode_insert_item,
        mode_move_item
      };

      DiagramScene(QObject* parent);
      ~DiagramScene();

    public:
      /*
      Set the current mode to use.
      Arguments:
      Mode mode: the mode to set

      Ex:
      scene->setMode(DiagramScene::Select);
    */
      inline void         SetMode(Mode mode) {
        current_mode_ = mode;
      }

      /*
      Set the current item to insert.
      Arguments:
      DiagramItem::Type item: the item to insert

      Ex:
      scene->setItem(DiagramItem::item_class);
    */
      inline void         SetItem(DiagramItem::Type item) {
        current_item_ = item;
      }

    private:
      Mode                current_mode_;
      DiagramItem::Type   current_item_;
    };
  }
}

#endif // _CPLUSPLUSML_UI_DIAGRAM_SCENE_H
