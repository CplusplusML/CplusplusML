#include <iostream> //DEBUG
#include "ui/complex_property_window.hh"

using namespace std; //DEBUG

namespace			CplusplusML
{
  // CTORS
  ComplexPropertyWindow::ComplexPropertyWindow():
    ui(new Ui::ComplexProperty)
  {
    ui->setupUi(this);

    // Connection for apply button
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton *)),
	    this, SLOT(checkApply(QAbstractButton *)));
    // Connections for attributes
    //   Buttons
    connect(ui->attrNewButton, SIGNAL(clicked()),
	    this, SLOT(createAttr()));
    connect(ui->attrDelButton, SIGNAL(clicked()),
	    this, SLOT(deleteAttr()));
    connect(ui->attrName, SIGNAL(editingFinished()),
    	    this, SLOT(updateAttrListItem()));
    connect(ui->attrType, SIGNAL(editingFinished()),
    	    this, SLOT(updateAttrListItem()));
    connect(ui->attrValue, SIGNAL(editingFinished()),
    	    this, SLOT(updateAttrListItem()));
    connect(ui->attrVisibility, SIGNAL(activated(int)),
    	    this, SLOT(updateAttrListItem()));
    connect(ui->attrIsStatic, SIGNAL(stateChanged(int)),
    	    this, SLOT(updateAttrListItem()));
    
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

  void				ComplexPropertyWindow::updateAttrListItem()
  {
    static char const * const	visibilities[3] = {"+", "#", "-"};
    QString			text;
    QListWidgetItem		*item;

    ui->attrName->setText(ui->attrName->text().trimmed());
    ui->attrType->setText(ui->attrType->text().trimmed());
    ui->attrValue->setText(ui->attrValue->text().trimmed());

    item = ui->attrList->currentItem();
    text += visibilities[ui->attrVisibility->currentIndex()];
    text += " " + ui->attrName->text();
    if (!ui->attrType->text().isEmpty())
      text += ": " + ui->attrType->text();
    if (!ui->attrValue->text().isEmpty())
      text += " = " + ui->attrValue->text();

    item->setText(text);
  }

  void				ComplexPropertyWindow::createAttr()
  {
    QListWidgetItem		*item;

    item = new QListWidgetItem("+");
    clearAttrData();
    ui->attrList->addItem(item);
    ui->attrList->setCurrentItem(item);

    if (!ui->attrGroupBox->isEnabled())
      {
	ui->attrGroupBox->setEnabled(true);
	ui->attrDelButton->setEnabled(true);
	ui->attrUpButton->setEnabled(true);
	ui->attrDownButton->setEnabled(true);
      }
    ui->attrName->setFocus(Qt::OtherFocusReason);
  }

  void				ComplexPropertyWindow::deleteAttr()
  {
    delete ui->attrList->currentItem();
    clearAttrData();
    if (!ui->attrList->count())
      {
	ui->attrGroupBox->setEnabled(false);
	ui->attrDelButton->setEnabled(false);
	ui->attrUpButton->setEnabled(false);
	ui->attrDownButton->setEnabled(false);
      }
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

  // PRIVATE FUNCTION
  void				ComplexPropertyWindow::clearAttrData()
  {
    ui->attrName->clear();
    ui->attrType->clear();
    ui->attrValue->clear();
    ui->attrVisibility->setCurrentIndex(0);
  }
  // !PRIVATE FUNCTION
}
