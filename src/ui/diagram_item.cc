#include "ui/diagram_item.h"

namespace     cplusplusml {
  namespace   ui {

    /*
      Initialie QGraphicsItem's parent.
    */
    DiagramItem::DiagramItem(QGraphicsItem* parent=NULL):
      QGraphicsItemGroup{parent} {
    }

    /*
      Destructor, do nothing.
    */
    DiagramItem::~DiagramItem() {
    }
  }
}
