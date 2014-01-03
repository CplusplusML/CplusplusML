#ifndef _CPLUSPLUSML_UI_MAIN_WINDOW_H_
#define _CPLUSPLUSML_UI_MAIN_WINDOW_H_

# include <QMainWindow>
# include <QCloseEvent>

# include "ui_main_window.h"

namespace     cplusplusml {
  namespace   ui {

    /*
      Main window object, created by the main function, it holds
      all the others Qt widgets.
    */
    class     MainWindow: public QMainWindow, private Ui::MainWindow {
      Q_OBJECT

    public:

      MainWindow();
      ~MainWindow();

    private slots:

      void    on_action_exit_triggered();

    private:

      void closeEvent(QCloseEvent* event);
    };

  }
}

#endif // _CPLUSPLUSML_UI_MAIN_WINDOW_H_
