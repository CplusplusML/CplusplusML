#include	<iostream>
#include	<QtGui>

#include	"ui/diagram_scene.hh"

#include	"object/class.hh"
#include	"object/struct.hh"
#include	"object/union.hh"


namespace			CplusplusML
{
  void				DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
  {
    Object::Basic_		*item;

    if (mouseEvent->button() != Qt::LeftButton)
      return;

    if (currentMode_ == modeInsertItem)
      {
	switch (currentItem_)
	  {
	  case (Object::objectClass):
	    item = new Object::Class();
	    break;
	  case (Object::objectStruct):
	    item = new Object::Struct();
	    break;
	  case (Object::objectUnion):
	    item = new Object::Union();
	    break;
	  default:
	    break;
	  };
    
	addItem(item);
	item->setPos(mouseEvent->scenePos());
      }

    QGraphicsScene::mousePressEvent(mouseEvent);
  }

  void				DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
  {
    if (currentMode_ == modeMoveItem)
      QGraphicsScene::mouseMoveEvent(mouseEvent);
  }
}
