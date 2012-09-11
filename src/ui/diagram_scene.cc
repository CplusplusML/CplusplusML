#include	<iostream>
#include	<list>
#include	<QtGui>

#include	"ui/diagram_scene.hh"

#include	"object/class.hh"
#include	"object/struct.hh"
#include	"object/union.hh"
#include	"object/dependency.hh"

#include	"assed.hpp"


namespace			CplusplusML
{

  DiagramScene::DiagramScene():
    currentItem_(Object::objectClass),
    currentMode_(modeMoveItem)
  {
    connect(&complexProperties_, SIGNAL(applied()), this, SLOT(applyProperties()));
    connect(this, SIGNAL(selectionChanged()), this, SLOT(myItemSelected()));
  }

  void				DiagramScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
  {
    Object::Complex_		*complex;

    if (mouseEvent->button() != Qt::LeftButton)
      return;

    if (!selectedItems().empty())
      {
	if ((complex = qgraphicsitem_cast<Object::Complex_ *>(selectedItems().first())))
	  complexProperties_.show(complex);
      }

    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
  }

  void				DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
  {
    Object::Basic_		*item = NULL;

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
            // case (Object::objectDependency):
            //   item = new Object::Dependency();
            //   break;
          default:
            break;
          };
        if (item != NULL)
          {
            item->setFlag(Object::Basic_::ItemIsSelectable, true);
            item->setSelected(true);
            item->setPos(mouseEvent->scenePos());
            addItem(item);
	    complexProperties_.show();
          }
      }

    QGraphicsScene::mousePressEvent(mouseEvent);
  }

  void				DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
  {
    if (currentMode_ == modeMoveItem)
      QGraphicsScene::mouseMoveEvent(mouseEvent);
  }

  void				DiagramScene::applyProperties()
  {
    Object::Complex_		*complex;

    if (!selectedItems().empty())
      {
	if ((complex = qgraphicsitem_cast<Object::Complex_ *>(selectedItems().first())))
	  complex->updateFromForm(complexProperties_);
      }
  }

  void				DiagramScene::myItemSelected()
  {
  }

}
