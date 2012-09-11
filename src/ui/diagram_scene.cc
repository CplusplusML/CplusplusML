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

  void				DiagramScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
  {
    
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
	    complexProperties_.clearAll();
	    complexProperties_.ui->name->setText("Test");
	    complexProperties_.show();
	    complexProperties_.dumpObjectTree();
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
	  {
	    complex->title_ = complexProperties_.ui->name->text().toStdString();
	    complex->isAbstract_ = complexProperties_.ui->isAbstract->checkState();
	    complex->setAttrVisible(complexProperties_.ui->isAttrVisible->checkState());
	    complex->setOpeVisible(complexProperties_.ui->isOpeVisible->checkState());
	    complex->update();
	  }
      }
  }

  void				DiagramScene::myItemSelected()
  {
  }

}
