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
    connect(ui->attrUpButton, SIGNAL(clicked()),
	    this, SLOT(selectUpAttrItem()));
    connect(ui->attrDownButton, SIGNAL(clicked()),
	    this, SLOT(selectDownAttrItem()));
    //   Edition
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

  void				ComplexPropertyWindow::selectUpAttrItem()
  {
    if (ui->attrList->count() > 1 && ui->attrList->currentRow() > 0)
      ui->attrList->setCurrentRow(ui->attrList->currentRow() - 1);
  }

  void				ComplexPropertyWindow::selectDownAttrItem()
  {
    if (ui->attrList->count() > 1 &&
	ui->attrList->currentRow() < (ui->attrList->count() - 1))
      ui->attrList->setCurrentRow(ui->attrList->currentRow() + 1);
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

    if (ui->attrList->count() > 1)
      {
	ui->attrUpButton->setEnabled(true);
	ui->attrDownButton->setEnabled(true);
      }
    if (!ui->attrGroupBox->isEnabled())
      {
	ui->attrGroupBox->setEnabled(true);
	ui->attrDelButton->setEnabled(true);
      }
    ui->attrName->setFocus(Qt::OtherFocusReason);
  }

  void				ComplexPropertyWindow::deleteAttr()
  {
    int				row = ui->attrList->currentRow();

    delete ui->attrList->currentItem();
    clearAttrData();
    if (ui->attrList->count())
      {
	if (row == ui->attrList->count())
	  ui->attrList->setCurrentRow(row - 1);
	else
	  ui->attrList->setCurrentRow(row);
	if (ui->attrList->count() < 2)
	  {
	    ui->attrUpButton->setEnabled(false);
	    ui->attrDownButton->setEnabled(false);
	  }
      }
    else
      {
	ui->attrGroupBox->setEnabled(false);
	ui->attrDelButton->setEnabled(false);
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
