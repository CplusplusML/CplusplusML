#ifndef _CPLUSPLUSML_UI_MAIN_W_H_
#define _CPLUSPLUSML_UI_MAIN_W_H_

#include <QMainWindow>
#include "ui_MainWindow.h"
#include "ui_AboutWindow.h"

#include "ui/diagram_scene.hh"
#include "object/basic.hh"

namespace CplusplusML
{
  class Main_W : public QMainWindow, Ui::MainWindow
  {
    Q_OBJECT
  public:
    Main_W();
    ~Main_W();

  public slots:
    void About();
    void WebSite();
    void Help();
    void manageToolbarActions(QAction *action);

  private:
    QDialog aboutWindow_;
    QDialog webSiteWindow_;
    QDialog helpWindow_;
    QDockWidget *toolbar_;
    DiagramScene scene_;
  };
}

#endif /* _CPLUSPLUSML_UI_MAIN_W_H_ */
