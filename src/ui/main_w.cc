#include <iostream>
#include <QApplication>
#include <QtGui>

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
      QGraphicsScene *scene = new QGraphicsScene();
      QLabel *title = new QLabel("Class0Lol");
      // title->resize(title->width(), title->height());
      title->setFixedWidth(200);
      std::cout << title->width() << "))((" << title->height() << std::endl;
      title->setAlignment( Qt::AlignCenter );
      title->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
      QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
      proxy->setWidget(title);

      // group->addToGroup (proxy)
      // proxy->setFlag(QGraphicsItem::ItemIsMovable, true);


      QRect titleBox(0, 0, title->width(), 50);

      // QPainterPath path;
      // path.moveTo(0, 0);
      // path.arcTo(150, 0, 50, 50, 0, 90);
      // path.arcTo(50, 0, 50, 50, 90, 90);
      // path.arcTo(50, 50, 50, 50, 180, 90);
      // path.arcTo(150, 50, 50, 50, 270, 90);
      // path.lineTo(200, 25);
      // QPolygonF myPolygon = path.toFillPolygon();
      // QGraphicsPolygonItem *polygon = new QGraphicsPolygonItem(myPolygon);
      QGraphicsPolygonItem *polygon = new QGraphicsPolygonItem(static_cast<const QRectF &>(titleBox));
      QGraphicsItemGroup *group = scene->createItemGroup({proxy, polygon});
      group->setFlag(QGraphicsItem::ItemIsMovable, true);
      // scene->addItem(group);
      // scene;
      graphicsView->setScene(scene);
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
