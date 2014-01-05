#include "ui/diagram_scene.h"

namespace         cplusplusml {
  namespace       ui {

    /*
      Constructor of the diagram scene, initialize the members and the parent
      QObject.
    */
    DiagramScene::DiagramScene(QObject* parent=0):
      QGraphicsScene{parent},
      current_mode_{Select} {
      }

    /*
      Destructor of the scene, do nothing
    */
    DiagramScene::~DiagramScene() {
    }

    /*
      Set the current mode to use.
      Arguments:
      Mode mode: the mode to set

      Ex:
      scene->setMode(DiagramScene::Select);
    */
    inline void   DiagramScene::setMode(Mode mode) {
      current_mode_ = mode;
    }
  }
}
