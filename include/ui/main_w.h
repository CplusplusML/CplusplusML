#ifndef _CPLUSPLUSML_UI_MAIN_W_H_
#define _CPLUSPLUSML_UI_MAIN_W_H_

#include <QMainWindow>
#include "ui_MainWindow.h"
#include "ui_AboutWindow.h"

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
  private:
    QDialog aboutWindow_;
  };
}

#endif /* _CPLUSPLUSML_UI_MAIN_W_H_ */
