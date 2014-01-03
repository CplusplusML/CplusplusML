#include <QApplication>

#include "ui/main_window.h"

/*
  Starting point of the program, create the application and run it.
  Arguments:
  int argc: number of arguments given to the program
  char *argv[]: array containing the arguments as strings
*/
  int     main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    cplusplusml::ui::MainWindow main_window;

    main_window.setGeometry(100, 100, 800, 500);
    main_window.show();

    return (app.exec());
  }
