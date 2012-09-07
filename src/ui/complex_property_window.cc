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
	    this, SLOT(moveUpAttrItem()));
    connect(ui->attrDownButton, SIGNAL(clicked()),
	    this, SLOT(moveDownAttrItem()));
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
    connect(ui->attrList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
	    this, SLOT(updateAttrData()));
    
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

  void				ComplexPropertyWindow::moveUpAttrItem()
  {
    int				currentRow = ui->attrList->currentRow();

    if (currentRow <= 0)
      return;

    QListWidgetItem * currentItem = ui->attrList->takeItem(currentRow);
    ui->attrList->insertItem(currentRow - 1, currentItem);
    ui->attrList->setCurrentRow(currentRow - 1);
    ui->attrUpButton->setEnabled(currentRow - 1 > 0);
  }

  void				ComplexPropertyWindow::moveDownAttrItem()
  {
    int currentRow = ui->attrList->currentRow();

    if (currentRow >= ui->attrList->count() - 1)
      return;

    QListWidgetItem * currentItem = ui->attrList->takeItem(currentRow);
    ui->attrList->insertItem(currentRow + 1, currentItem);
    ui->attrList->setCurrentRow(currentRow + 1);
    ui->attrDownButton->setEnabled(currentRow + 2 < ui->attrList->count());
  }

  void				ComplexPropertyWindow::updateAttrListItem()
  {
    QListWidgetItem		*item;
    Object::Members::Attribute	*attr;

    ui->attrName->setText(ui->attrName->text().trimmed());
    ui->attrType->setText(ui->attrType->text().trimmed());
    ui->attrValue->setText(ui->attrValue->text().trimmed());

    item = ui->attrList->currentItem();
    attr = attributes_[item];
    attr->name = ui->attrName->text().toStdString();
    attr->type = ui->attrType->text().toStdString();
    attr->defaultValue = ui->attrValue->text().toStdString();
    attr->visibility = static_cast<Object::Members::Visibility>(ui->attrVisibility->currentIndex());
    attr->isStatic = static_cast<bool>(ui->attrIsStatic->checkState());
    item->setText(attr->toString().c_str());
  }

  void				ComplexPropertyWindow::updateAttrData()
  {
    QListWidgetItem		*item;
    Object::Members::Attribute	*attr;

    if (ui->attrList->currentRow() < 0)
      return;

    clearAttrData();
    cerr << ui->attrList->count() << endl;
    item = ui->attrList->currentItem();
    attr = attributes_[item];
    ui->attrName->setText(attr->name.c_str());
    ui->attrType->setText(attr->type.c_str());
    ui->attrValue->setText(attr->defaultValue.c_str());
    ui->attrVisibility->setCurrentIndex(static_cast<int>(attr->visibility));
    ui->attrIsStatic->setCheckState(static_cast<Qt::CheckState>(static_cast<int>(attr->isStatic) * 2));
    ui->attrUpButton->setEnabled(ui->attrList->currentRow() > 0);
    ui->attrDownButton->setEnabled(ui->attrList->currentRow() + 1 < ui->attrList->count());
  }

  void				ComplexPropertyWindow::createAttr()
  {
    QListWidgetItem		*item;
    
    item = new QListWidgetItem("+");
    clearAttrData();
    attributes_[item] = new Object::Members::Attribute;
    ui->attrList->addItem(item);
    if (!ui->attrGroupBox->isEnabled())
      {
	ui->attrGroupBox->setEnabled(true);
	ui->attrDelButton->setEnabled(true);
      }
    ui->attrName->setFocus(Qt::OtherFocusReason);
    ui->attrList->setCurrentItem(item);
    ui->attrUpButton->setEnabled(ui->attrList->currentRow() > 0);
    ui->attrDownButton->setEnabled(ui->attrList->currentRow() + 1 < ui->attrList->count());
  }

  void				ComplexPropertyWindow::deleteAttr()
  {
    int				row = ui->attrList->currentRow();
    QListWidgetItem		*item;

    clearAttrData();
    item = ui->attrList->takeItem(row);
    attributes_.erase(item);
    delete item;
    if (!ui->attrList->count())
      {
	ui->attrGroupBox->setEnabled(false);
	ui->attrDelButton->setEnabled(false);
      }
  ui->attrUpButton->setEnabled(ui->attrList->currentRow() > 0);
  ui->attrDownButton->setEnabled(ui->attrList->currentRow() + 1 < ui->attrList->count());
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
    // Attributes
    clearAttrData();
    ui->attrList->clear();
    ui->attrGroupBox->setEnabled(false);
    ui->attrDelButton->setEnabled(false);
    ui->attrUpButton->setEnabled(false);
    ui->attrDownButton->setEnabled(false);

    // List of attributes and operations
    attributes_.clear();
    operations_.clear();
  }

  void				ComplexPropertyWindow::show()
  {
    this->clearAll();
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
