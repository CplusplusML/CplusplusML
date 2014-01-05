#include "ui/diagram_scene.h"

namespace         cplusplusml {
  namespace       ui {

    /*
      Constructor of the diagram scene, initialize the members and the parent
      QObject.
    */
    DiagramScene::DiagramScene(QObject* parent=0):
      QGraphicsScene{parent},
      current_mode_{mode_select},
      current_item_{DiagramItem::item_cursor} {
      }

    /*
      Destructor of the scene, do nothing
    */
    DiagramScene::~DiagramScene() {
    }
  }
}
