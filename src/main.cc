#include "ui/main_w.h"

int main(int argc, char *argv[])
{
	  QApplication app(argc, argv);
    CplusplusML::Main_W mainWindow;

    mainWindow.show();
    return app.exec();
}
