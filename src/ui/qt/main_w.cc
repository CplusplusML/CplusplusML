#include        <iostream>
#include        <map>
#include        <QApplication>
#include        <QtGui>
#include        <QDesktopServices>

#include        "ui/qt/main_w.h"
#include        "ui_AboutWindow.h"
#include        "ui_HelpWindow.h"

#include        "object/class.hh"
//#include "object/dependency.hh"


namespace               CplusplusML
{
  namespace             Ui
  {
    namespace           Qt
    {
      Main_W::Main_W()
      {
        setupUi(this);

        {
          ::Ui::AboutWindow     about_window_ui;
          about_window_ui.setupUi(&aboutWindow_);
          connect(actionAbout_C_Ml, SIGNAL(triggered()), this, SLOT(About()));

          connect(actionC_Website, SIGNAL(triggered()), this, SLOT(WebSite()));

          ::Ui::HelpWindow      help_window_ui;
          help_window_ui.setupUi(&helpWindow_);
          connect(actionHelp, SIGNAL(triggered()), this, SLOT(Help()));

          connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));

          QActionGroup* toolbarActionGroup = new QActionGroup(this);

          toolbarActionGroup->setExclusive(true);

          actionCursor->setChecked(true);
          toolbarActionGroup->addAction(actionCursor);
          toolbarActionGroup->addAction(actionNamespace);
          toolbarActionGroup->addAction(actionClass);
          toolbarActionGroup->addAction(actionStruct);
          toolbarActionGroup->addAction(actionTypedef);
          toolbarActionGroup->addAction(actionEnum);
          toolbarActionGroup->addAction(actionUnion);
          toolbarActionGroup->addAction(actionInheritance);
          toolbarActionGroup->addAction(actionComposition);
          toolbarActionGroup->addAction(actionAggregation);
          toolbarActionGroup->addAction(actionDependency);
          toolbarActionGroup->addAction(actionTemplateParameter);
          toolbarActionGroup->addAction(actionTemplateSpecialization);
          toolbarActionGroup->addAction(actionTemplateSpecializationParameter);
          toolbarActionGroup->addAction(actionFreeFunction);
          toolbarActionGroup->addAction(actionTemplate);
          toolbarActionGroup->addAction(actionLibrary);
          connect(toolbarActionGroup, SIGNAL(selected(QAction *)),
                  this, SLOT(ManageToolbarActions(QAction *)));

          toolBar->addActions(toolbarActionGroup->actions());
          toolBar->insertSeparator(actionNamespace);
          toolBar->insertSeparator(actionDependency);
          toolBar->insertSeparator(actionInheritance);
          toolBar->insertSeparator(actionTemplateParameter);
          toolBar->insertSeparator(actionFreeFunction);

        }

        // scene
        {
          scene_.setSceneRect(QRectF(0, 0, 2000, 2000));
          connect(&scene_, SIGNAL(ItemInserted(QGraphicsItem*)), this, SLOT(SetDefaultAction()));

          graphicsView->setScene(&scene_);
        }

        //    aboutWindow_.show();

      }

      Main_W::~Main_W()
      {
      }

      void Main_W::About()
      {
        aboutWindow_.show();
      }

      void Main_W::WebSite()
      {
        QDesktopServices::openUrl(QUrl("http://cplusplusml.org"));
      }

      void Main_W::Help()
      {
        helpWindow_.show();
      }

      void Main_W::ManageToolbarActions(QAction *action)
      {
        static const std::map<QAction *, Object::Type> objectMap = {
          {actionCursor, Object::Type::objectCursor},
          {actionNamespace, Object::Type::objectNamespace},
          {actionClass, Object::Type::objectClass},
          {actionStruct, Object::Type::objectStruct},
          {actionEnum, Object::Type::objectEnum},
          {actionUnion, Object::Type::objectUnion},
          {actionTypedef, Object::Type::objectTypedef},
          {actionAggregation, Object::Type::objectAggregation},
          {actionDependency, Object::Type::objectDependency},
          {actionComposition, Object::Type::objectComposition},
          {actionInheritance, Object::Type::objectInheritance},
          {actionTemplateParameter, Object::Type::objectTemplateParameter},
          {actionTemplateSpecialization, Object::Type::objectTemplateSpecialization},
          {actionTemplateSpecializationParameter, Object::Type::objectTemplateSpecializationParameter},
          {actionFreeFunction, Object::Type::objectFreeFunction},
          {actionTemplate, Object::Type::objectMetaClassificator},
          {actionLibrary, Object::Type::objectLibrary}
        };

        std::map<QAction *, Object::Type>::const_iterator found;
        found = objectMap.find(action);

        if (found == objectMap.end())
          {
            std::cerr << "Action not found" << std::endl;
            return;
          }
        if (found->second == Object::Type::objectCursor)
          scene_.SetMode(DiagramScene::modeMoveItem);
        else
          {
            scene_.SetMode(DiagramScene::modeInsertItem);
            scene_.SetCurrentItem(found->second);
          }
      }

      void Main_W::SetDefaultAction()
      {
        actionCursor->activate(QAction::Trigger);
      }
    }
  }
}
