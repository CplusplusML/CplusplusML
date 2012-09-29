#include "ui/qt/main_w.h"

int main(int argc, char *argv[])
{
	  QApplication app(argc, argv);
    QApplication::setStyle("plastique");
    CplusplusML::Ui::Qt::Main_W mainWindow;

    mainWindow.show();
    return app.exec();
}
