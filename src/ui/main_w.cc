#include <iostream>
#include "ui/main_w.h"
#include "ui_AboutWindow.h"
#include "ui_WebSiteWindow.h"
#include "ui_HelpWindow.h"
#include "ui_ToolsBar.h"

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

      toolBar->addAction(actionCursor);
      toolBar->addAction(actionNamespace);
      toolBar->addAction(actionClass);
      toolBar->addAction(actionStruct);
      toolBar->addAction(actionTypedef);
      toolBar->addAction(actionEnum);
      toolBar->addAction(actionUnion);
      toolBar->addAction(actionAggregation);
      toolBar->addAction(actionDependency);
      toolBar->addAction(actionComposition);
      toolBar->addAction(actionInheritance);
      toolBar->addAction(actionFreeFunction);
      toolBar->addAction(actionTemplate);
      toolBar->addAction(actionLibrary);
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
