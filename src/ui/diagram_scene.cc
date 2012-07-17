#include	<iostream>
#include	<QtGui>

#include	"ui/diagram_scene.hh"

namespace			CplusplusML
{
  void				DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
  {
    Object::Basic_		*item;

    if (mouseEvent->button() != Qt::LeftButton)
      return;

    // switch (currentItem_)
    //   {
    //   case (objectClass):
    // 	item = new Object::Class();
    // 	break;
    //   case (objectStruct):
    // 	item = new Object::Struct();
    // 	break;
    //   case (objectUnion):
    // 	item = new Object::Union();
    // 	break;
    //   default:
    // 	break;
    //   };
    
    // item->setPos(mouseEvent->scenePos());
    // addItem(item);

    QGraphicsScene::mousePressEvent(mouseEvent);
  }

  void				DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
  {
    if (currentMode_ == modeMoveItem)
      QGraphicsScene::mouseMoveEvent(mouseEvent);
  }
}
