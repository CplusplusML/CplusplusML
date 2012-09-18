#include <iostream>
#include <map>
#include <QApplication>
#include <QtGui>
#include <QDesktopServices>

#include "ui/main_w.h"
#include "ui_AboutWindow.h"
#include "ui_WebSiteWindow.h"
#include "ui_HelpWindow.h"

#include "object/class.hh"
#include "object/dependency.hh"


namespace CplusplusML
{
  Main_W::Main_W()
  {
    setupUi(this);

    {
      Ui::AboutWindow	about_window_ui;
      about_window_ui.setupUi(&aboutWindow_);
      connect(actionAbout_C_Ml, SIGNAL(triggered()), this, SLOT(About()));

      Ui::WebSiteWindow	web_site_window_ui;
      web_site_window_ui.setupUi(&webSiteWindow_);
      connect(actionC_Website, SIGNAL(triggered()), this, SLOT(WebSite()));

      Ui::HelpWindow	help_window_ui;
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
      toolbarActionGroup->addAction(actionAggregation);
      toolbarActionGroup->addAction(actionDependency);
      toolbarActionGroup->addAction(actionComposition);
      toolbarActionGroup->addAction(actionInheritance);
      toolbarActionGroup->addAction(actionFreeFunction);
      toolbarActionGroup->addAction(actionTemplate);
      toolbarActionGroup->addAction(actionLibrary);
      connect(toolbarActionGroup, SIGNAL(selected(QAction *)), this, SLOT(manageToolbarActions(QAction *)));

      toolBar->addActions(toolbarActionGroup->actions());
      toolBar->insertSeparator(actionNamespace);
      toolBar->insertSeparator(actionAggregation);
      toolBar->insertSeparator(actionFreeFunction);

    }

    // scene
    {
      scene_.setSceneRect(QRectF(0, 0, 2000, 2000));

      graphicsView->setScene(&scene_);
    }

    aboutWindow_.show();

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

  void Main_W::manageToolbarActions(QAction *action)
  {
    static const std::map<QAction *, Object::ObjectType> objectMap = {
      {actionCursor, Object::objectCursor},
      {actionNamespace, Object::objectNamespace},
      {actionClass, Object::objectClass},
      {actionStruct, Object::objectStruct},
      {actionEnum, Object::objectEnum},
      {actionUnion, Object::objectUnion},
      {actionTypedef, Object::objectTypedef},
      {actionAggregation, Object::objectAggregation},
      {actionDependency, Object::objectDependency},
      {actionComposition, Object::objectComposition},
      {actionInheritance, Object::objectInheritance},
      {actionFreeFunction, Object::objectFreeFunction},
      {actionTemplate, Object::objectTemplate},
      {actionLibrary, Object::objectLibrary}
    };

    std::map<QAction *, Object::ObjectType>::const_iterator found;
    found = objectMap.find(action);

    if (found == objectMap.end())
      {
	std::cerr << "Action not found" << std::endl;
	return;
      }
    if (found->second == Object::objectCursor)
      scene_.setMode(DiagramScene::modeMoveItem);
    else
      {
	scene_.setMode(DiagramScene::modeInsertItem);
	scene_.setCurrentItem(found->second);
      }
  }
}

