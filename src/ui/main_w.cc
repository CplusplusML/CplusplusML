#include <iostream>
#include <map>
#include <QApplication>
#include <QtGui>
#include <QDesktopServices>
#include <QtGlobal>

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

      // Zoom
      {
      QActionGroup* zoomActionGroup = new QActionGroup(this);

      zoomActionGroup->setExclusive(true);

      zoomActionGroup->addAction(action200);
      zoomActionGroup->addAction(action175);
      zoomActionGroup->addAction(action150);
      zoomActionGroup->addAction(action125);
      zoomActionGroup->addAction(action100);
      zoomActionGroup->addAction(action85);
      zoomActionGroup->addAction(action50);
      zoomActionGroup->addAction(action25);
      zoomActionGroup->addAction(actionZoom);
      zoomActionGroup->addAction(actionZoom_2);
      connect(zoomActionGroup, SIGNAL(selected(QAction *)), this, SLOT(Zoom(QAction *)));
      }
      // end Zoom

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

  void Main_W::Zoom(QAction *action)
  {
    qreal factor;

    static const std::map<QAction *, qreal> objectMap=
      {
        {action25, 0.25},
        {action50, 0.5},
        {action85, 0.75},
        {action100, 1},
        {action125, 1.25},
        {action150, 1.5},
        {action175, 1.75},
        {action200, 2},
      };

    if (action == actionZoom)
      factor = 1.2;
    else if (action == actionZoom_2)
      factor = 1 / 1.2;
    else
      {
        std::map<QAction *, qreal>::const_iterator found;
        found = objectMap.find(action);
        if (found == objectMap.end())
          {
            std::cerr << "Action not found" << std::endl;
            return;
          }
        factor = (1 / scene_.getScale()) * found->second;
      }
    scene_.scaleBy(factor);
    graphicsView->scale(factor, factor);
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

