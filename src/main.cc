#include "ui/main_w.h"

int main(int argc, char *argv[])
{
	  QApplication app(argc, argv);
    QApplication::setStyle("plastique");
    CplusplusML::Main_W mainWindow;

    mainWindow.show();
    return app.exec();
}
