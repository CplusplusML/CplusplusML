#include        <iostream>
#include        <list>
#include        <QtGui>

#include        "ui/qt/diagram_scene.hh"
#include        "ui/qt/classificator_graphic_item.hh"

#include        "object/class.hh"
#include        "object/struct.hh"
#include        "object/union.hh"
#include        "object/meta_classificator.hh"

//#include	"object/dependency.hh"
#include        "assed.hpp"


namespace               CplusplusML
{
  namespace             Ui
  {
    namespace           Qt
    {
      DiagramScene::DiagramScene():
        currentItem_(Object::Type::objectClass),
        currentMode_(modeMoveItem)
      {
        connect(&classificatorProperties_, SIGNAL(Applied()),
                this, SLOT(ApplyProperties_()));
        connect(this, SIGNAL(selectionChanged()),
                this, SLOT(MyItemSelected_()));
      }

      void              DiagramScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
      {
        Classificator   *classificator;

        if (mouseEvent->button() != ::Qt::LeftButton)
          return;

        if (!selectedItems().empty())
          {
            if ((classificator = qgraphicsitem_cast<Classificator *>(selectedItems().first())))
              classificatorProperties_.Show(classificator->GetObject());
          }

        QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
      }

      void              DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
      {
        QGraphicsItem   *item = NULL;

        if (mouseEvent->button() != ::Qt::LeftButton)
          return;

        if (currentMode_ == modeInsertItem)
          {
            switch (currentItem_)
              {
              case (Object::Type::objectClass):
                item = new Classificator(new Object::Class());
                break;
              case (Object::Type::objectStruct):
                item = new Classificator(new Object::Struct());
                break;
              case (Object::Type::objectUnion):
                item = new Classificator(new Object::Union());
                break;
              case (Object::Type::objectMetaClassificator):
                item = new Classificator(new Object::MetaClassificator());
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
                item->setFlag(Classificator::ItemIsSelectable, true);
                item->setFlag(Classificator::ItemIsMovable, true);
                item->setPos(mouseEvent->scenePos());
                addItem(item);
                SetMode(modeMoveItem);
                emit ItemInserted(item);
              }
          }

        QGraphicsScene::mousePressEvent(mouseEvent);
      }

      void              DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
      {
        if (currentMode_ == modeMoveItem)
          QGraphicsScene::mouseMoveEvent(mouseEvent);
      }

      void              DiagramScene::ApplyProperties_()
      {
        Classificator   *clGrItem;

        if (!selectedItems().empty())
          {
            if ((clGrItem = qgraphicsitem_cast<Classificator *>(selectedItems().first())))
              {
                clGrItem->GetObject()->UpdateFromForm(*classificatorProperties_.ui);
                clGrItem->update();
              }
          }
      }

      void              DiagramScene::MyItemSelected_()
      {
      }
    }
  }
}
