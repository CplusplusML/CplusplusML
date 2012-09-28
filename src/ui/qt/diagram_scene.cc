#include        <iostream>
#include        <list>
#include        <QtGui>

#include        "ui/qt/diagram_scene.hh"
#include        "ui/qt/classificator_graphic_item.hh"

#include        "object/class.hh"
#include        "object/struct.hh"
#include        "object/union.hh"
#include        "object/template_param.hh"

//#include	"object/dependency.hh"
#include        "assed.hpp"


namespace			CplusplusML
{
  DiagramScene::DiagramScene():
    currentItem_(Object::Type::objectClass),
    currentMode_(modeMoveItem)
  {
    connect(&classificatorProperties_, SIGNAL(Applied()), this, SLOT(applyProperties()));
    connect(this, SIGNAL(selectionChanged()), this, SLOT(myItemSelected()));
  }

  void				DiagramScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
  {
    Ui::Qt::Classificator *classificator;

    if (mouseEvent->button() != Qt::LeftButton)
      return;

    if (!selectedItems().empty())
      {
        if ((classificator = qgraphicsitem_cast<Ui::Qt::Classificator *>(selectedItems().first())))
          classificatorProperties_.Show(classificator->GetObject());
      }

    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
  }

  void                  DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
  {
    QGraphicsItem      *item = NULL;

    if (mouseEvent->button() != Qt::LeftButton)
      return;

    if (currentMode_ == modeInsertItem)
      {
        switch (currentItem_)
          {
          case (Object::Type::objectClass):
            item = new Ui::Qt::Classificator(new Object::Class());
            break;
          case (Object::Type::objectStruct):
            item = new Ui::Qt::Classificator(new Object::Struct());
            break;
          case (Object::Type::objectUnion):
            item = new Ui::Qt::Classificator(new Object::Union());
            break;
          case (Object::Type::objectTemplate):
            item = new Ui::Qt::Classificator(new Object::TemplateParam());
            break;
            // case (Object::Type::objectDependency):
            //   item = new Object::Dependency();
            //   break;
          default:
            break;
          };
        if (item != NULL)
          {
            item->setSelected(true);
            item->setFlag(Ui::Qt::Classificator::ItemIsSelectable, true);
            item->setPos(mouseEvent->scenePos());
            addItem(item);
            setMode(modeMoveItem);
            emit itemInserted(item);
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
    Ui::Qt::Classificator       *clGrItem;

    if (!selectedItems().empty())
      {
        if ((clGrItem = qgraphicsitem_cast<Ui::Qt::Classificator *>(selectedItems().first())))
          clGrItem->GetObject()->UpdateFromForm(*classificatorProperties_.ui);
      }
  }

  void				DiagramScene::myItemSelected()
  {
  }

}
