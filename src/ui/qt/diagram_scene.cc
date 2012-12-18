#include        <iostream>
#include        <list>
#include        <QtGui>

#include        "ui/qt/diagram_scene.hh"
#include        "ui/qt/classificator_graphic_item.hh"
#include        "ui/qt/aggregation_graphics_item.hh"
#include        "ui/qt/dependency_graphics_item.hh"
#include        "ui/qt/composition_graphics_item.hh"
#include        "ui/qt/inheritance_graphics_item.hh"
#include        "ui/qt/template_parameter_graphics_item.hh"
#include        "ui/qt/template_specialization_graphics_item.hh"
#include        "ui/qt/template_specialization_parameter_graphics_item.hh"

#include        "object/class.hh"
#include        "object/struct.hh"
#include        "object/union.hh"
#include        "object/meta_classificator.hh"
#include        "object/dependency.hh"

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
            if ((classificator = dynamic_cast<Classificator *>(selectedItems().first())))
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
              case (Object::Type::objectAggregation):
                item = new Aggregation();
                break;
              case (Object::Type::objectDependency):
                item = new Dependency();
                break;
              case (Object::Type::objectComposition):
                item = new Composition();
                break;
              case (Object::Type::objectInheritance):
                item = new Inheritance();
                break;
              case (Object::Type::objectTemplateParameter):
                item = new TemplateParameter();
                break;
              case (Object::Type::objectTemplateSpecialization):
                item = new TemplateSpecialization();
                break;
              case (Object::Type::objectTemplateSpecializationParameter):
                item = new TemplateSpecializationParameter();
                break;
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
                qDebug() << "Item created: " << item;
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
              clGrItem->GetObject()->UpdateFromForm(*classificatorProperties_.ui);
          }
      }

      void              DiagramScene::MyItemSelected_()
      {
      }
    }
  }
}
