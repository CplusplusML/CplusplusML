#include <iostream>
#include <QApplication>
#include <QtGui>

#include "ui/main_w.h"
#include "ui_AboutWindow.h"
#include "ui_WebSiteWindow.h"
#include "ui_HelpWindow.h"

#include "object/class.hh"


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

      QActionGroup* actionGroup = new QActionGroup(this);

      actionGroup->setExclusive(true);

      actionGroup->addAction(actionCursor);
      actionGroup->addAction(actionNamespace);
      actionGroup->addAction(actionClass);
      actionGroup->addAction(actionStruct);
      actionGroup->addAction(actionTypedef);
      actionGroup->addAction(actionEnum);
      actionGroup->addAction(actionUnion);
      actionGroup->addAction(actionAggregation);
      actionGroup->addAction(actionDependency);
      actionGroup->addAction(actionComposition);
      actionGroup->addAction(actionInheritance);
      actionGroup->addAction(actionFreeFunction);
      actionGroup->addAction(actionTemplate);
      actionGroup->addAction(actionLibrary);
      toolBar->addActions(actionGroup->actions());
      toolBar->insertSeparator(actionNamespace);
      toolBar->insertSeparator(actionAggregation);
      toolBar->insertSeparator(actionFreeFunction);
    }

    // scene
    {
      Object::Class test;
      test.Render(scene_);

      Object::Class test2;
      test2.Render(scene_);

      graphicsView->setScene(&scene_);
    }
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
    webSiteWindow_.show();
  }

  void Main_W::Help()
  {
    helpWindow_.show();
  }
}

