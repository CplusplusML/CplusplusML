#include <iostream> //DEBUG
#include "ui/complex_property_window.hh"

using namespace std; // DEBUG

namespace			CplusplusML
{
  // CTORS
  ComplexPropertyWindow::ComplexPropertyWindow():
    ui(new Ui::ComplexProperty)
  {
    ui->setupUi(this);

    // Signal -> slots
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton *)),
	    this, SLOT(checkApply(QAbstractButton *)));
    connect(ui->attrNewButton, SIGNAL(clicked()), this, SLOT(createNewAttr()));
  }
  // !CTORS

  // DTORS
  ComplexPropertyWindow::~ComplexPropertyWindow()
  {
    delete ui;
  }
  // !DTORS

  // PRIVATE SLOTS
  void				ComplexPropertyWindow::checkApply(QAbstractButton *button)
  {
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Apply ||
	ui->buttonBox->standardButton(button) == QDialogButtonBox::Ok)
      emit applied();
  }

  void				ComplexPropertyWindow::createNewAttr()
  {
    
  }

  void				ComplexPropertyWindow::createNewOpe()
  {

  }

  void				ComplexPropertyWindow::createNewOpeParam()
  {

  }
  // !PRIVATE SLOTS

  // PUBLIC FUNCTIONS
  void				ComplexPropertyWindow::clearAll()
  {
    
  }

  void				ComplexPropertyWindow::show()
  {
    QDialog::show();
  }
  // !PUBLIC FUNCTIONS
}
