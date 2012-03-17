#include <QMainWindow>

#include "ui_MainWindow.h"

int main(int argc, char *argv[])
{
	  QApplication app(argc, argv);
    QMainWindow mainWindow;

		Ui::MainWindow			mainWindow_UI;

		mainWindow_UI.setupUi(&mainWindow);
    mainWindow.show();
    return app.exec();
}
