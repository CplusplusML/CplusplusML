#include <iostream>

#include "ui/main_window.h"

namespace     cplusplusml {
  namespace   ui {

    /*
      Constructor of MainWindow, initialize the User Interface.
    */
    MainWindow::MainWindow() {
      setupUi(this);
    }

    /*
      Destructor of MainWindow, do nothing
    */
    MainWindow::~MainWindow() {

    }

    /*
      When the button exit from the file menu is triggered,
      close the main window.
    */
    void      MainWindow::on_action_exit_triggered() {
      close();
    }

    /*
      When the close event is triggered, ask for the user to save
      unsaved documents.
      Arguments:
      QCloseEvent event: closing event
    */
      void    MainWindow::closeEvent(QCloseEvent *event) {
        event->accept();
      }
  }
}
