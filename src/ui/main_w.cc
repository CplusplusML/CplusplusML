#include <iostream>
#include "ui/main_w.h"
#include "ui_AboutWindow.h"

namespace CplusplusML
{
  Main_W::Main_W()
  {
    setupUi(this);

    {
      Ui::AboutWindow   ui;
      ui.setupUi(&aboutWindow_);
      connect(actionAbout_C_Ml, SIGNAL(triggered()), this, SLOT(About()));
    }
  }

  Main_W::~Main_W()
  {
  }

  void Main_W::About()
  {
    aboutWindow_.show();
  }
}
