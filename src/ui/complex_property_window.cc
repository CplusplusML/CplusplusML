#include <iostream> //DEBUG

#include "ui/complex_property_window.hh"
#include "object/complex.hh"

using namespace std; //DEBUG

namespace			CplusplusML
{
  // CTORS
  ComplexPropertyWindow::ComplexPropertyWindow():
    ui(new Ui::ComplexProperty),
    complex_(NULL)
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
    // Connection for operations
    //   Buttons
    //     Operations
    connect(ui->opeNewButton, SIGNAL(clicked()),
	    this, SLOT(createOpe()));
    connect(ui->opeDelButton, SIGNAL(clicked()),
	    this, SLOT(deleteOpe()));
    connect(ui->opeUpButton, SIGNAL(clicked()),
	    this, SLOT(moveUpOpeItem()));
    connect(ui->opeDownButton, SIGNAL(clicked()),
	    this, SLOT(moveDownOpeItem()));
    //     Parameters
    connect(ui->opeParamNewButton, SIGNAL(clicked()),
	    this, SLOT(createOpeParam()));
    connect(ui->opeParamDelButton, SIGNAL(clicked()),
	    this, SLOT(deleteOpeParam()));
    connect(ui->opeParamUpButton, SIGNAL(clicked()),
	    this, SLOT(moveUpOpeParamItem()));
    connect(ui->opeParamDownButton, SIGNAL(clicked()),
	    this, SLOT(moveDownOpeParamItem()));
    //   Edition
    //     Operations
    connect(ui->opeName, SIGNAL(editingFinished()),
    	    this, SLOT(updateOpeListItem()));
    connect(ui->opeType, SIGNAL(editingFinished()),
    	    this, SLOT(updateOpeListItem()));
    connect(ui->opeVisibility, SIGNAL(activated(int)),
    	    this, SLOT(updateOpeListItem()));
    connect(ui->opeIsStatic, SIGNAL(stateChanged(int)),
    	    this, SLOT(updateOpeListItem()));
    connect(ui->opeIsConst, SIGNAL(stateChanged(int)),
    	    this, SLOT(updateOpeListItem()));
    connect(ui->opeList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
	    this, SLOT(updateOpeData()));
    //     Parameters
    connect(ui->opeParamName, SIGNAL(editingFinished()),
    	    this, SLOT(updateOpeParamListItem()));
    connect(ui->opeParamType, SIGNAL(editingFinished()),
    	    this, SLOT(updateOpeParamListItem()));
    connect(ui->opeParamValue, SIGNAL(editingFinished()),
    	    this, SLOT(updateOpeParamListItem()));
  }
  // !CTORS

  // DTORS
  ComplexPropertyWindow::~ComplexPropertyWindow()
  {
    delete ui;
  }
  // !DTORS

  // PRIVATE SLOTS
  // ATTRIBUTES
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

  // Update the list view, get data from form and make a string displayed into the list item
  void				ComplexPropertyWindow::updateAttrListItem()
  {
    MemberListItem		*item;
    Object::Members::Attribute	*attr;

    ui->attrName->setText(ui->attrName->text().trimmed());
    ui->attrType->setText(ui->attrType->text().trimmed());
    ui->attrValue->setText(ui->attrValue->text().trimmed());

    item = static_cast<MemberListItem *>(ui->attrList->currentItem());
    attr = static_cast<Object::Members::Attribute *>(item->tmpMember_);
    attr->name = ui->attrName->text().toStdString();
    attr->type = ui->attrType->text().toStdString();
    attr->defaultValue = ui->attrValue->text().toStdString();
    attr->visibility = static_cast<Object::Members::Visibility>(ui->attrVisibility->currentIndex());
    attr->isStatic = ui->attrIsStatic->checkState();
    item->setText(attr->toString().c_str());
  }

  // When the selection change, update the attribute's data from the item in the list
  void				ComplexPropertyWindow::updateAttrData()
  {
    MemberListItem		*item;
    Object::Members::Attribute	*attr;

    if (ui->attrList->currentRow() < 0)
      return;

    clearAttrData();
    item = static_cast<MemberListItem *>(ui->attrList->currentItem());
    attr = static_cast<Object::Members::Attribute *>(item->tmpMember_);
    ui->attrName->setText(attr->name.c_str());
    ui->attrType->setText(attr->type.c_str());
    ui->attrValue->setText(attr->defaultValue.c_str());
    ui->attrVisibility->setCurrentIndex(static_cast<int>(attr->visibility));
    ui->attrIsStatic->setCheckState(static_cast<Qt::CheckState>(static_cast<int>(attr->isStatic) * 2));
    ui->attrUpButton->setEnabled(ui->attrList->currentRow() > 0);
    ui->attrDownButton->setEnabled(ui->attrList->currentRow() + 1 < ui->attrList->count());
    ui->attrName->setFocus(Qt::OtherFocusReason);    
  }

  void				ComplexPropertyWindow::createAttr()
  {
    MemberListItem		*item;
    
    item = new MemberListItem("+", new Object::Members::Attribute(true));
    clearAttrData();
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
    MemberListItem		*item;

    clearAttrData();
    item = static_cast<MemberListItem *>(ui->attrList->takeItem(row));
    if (item->member_)
      item->member_->deleted = true;
    delete item;
    if (!ui->attrList->count())
      {
	ui->attrGroupBox->setEnabled(false);
	ui->attrDelButton->setEnabled(false);
      }
    ui->attrUpButton->setEnabled(ui->attrList->currentRow() > 0);
    ui->attrDownButton->setEnabled(ui->attrList->currentRow() + 1 < ui->attrList->count());
  }
  
  // OPERATIONS

  void			ComplexPropertyWindow::createOpe()
  {
    MemberListItem		*item;
    
    item = new MemberListItem("+", new Object::Members::Operation(true));
    clearOpeData();
    ui->opeList->addItem(item);
    if (!ui->opeGroupBox->isEnabled())
      {
    	ui->opeGroupBox->setEnabled(true);
    	ui->opeDelButton->setEnabled(true);
      }
    ui->opeName->setFocus(Qt::OtherFocusReason);
    ui->opeList->setCurrentItem(item);
    ui->opeUpButton->setEnabled(ui->opeList->currentRow() > 0);
    ui->opeDownButton->setEnabled(ui->opeList->currentRow() + 1 < ui->opeList->count());
  }

  void			ComplexPropertyWindow::deleteOpe()
  {

  }

  void			ComplexPropertyWindow::updateOpeListItem()
  {

  }

  void			ComplexPropertyWindow::moveUpOpeItem()
  {

  }

  void			ComplexPropertyWindow::moveDownOpeItem()
  {

  }

  void			ComplexPropertyWindow::updateOpeData()
  {

  }

  void			ComplexPropertyWindow::createOpeParam()
  {

  }

  void			ComplexPropertyWindow::deleteOpeParam()
  {

  }

  void			ComplexPropertyWindow::updateOpeParamListItem()
  {

  }

  void			ComplexPropertyWindow::moveUpOpeParamItem()
  {

  }

  void			ComplexPropertyWindow::moveDownOpeParamItem()
  {

  }

  void			ComplexPropertyWindow::updateOpeParamData()
  {

  }


  // !PRIVATE SLOTS

  // PUBLIC FUNCTIONS
  void				ComplexPropertyWindow::clearAll()
  {
    // Attributes
    clearAttrData();
    clearOpeData();
    ui->attrList->clear();
    ui->opeList->clear();
    ui->attrGroupBox->setEnabled(false);
    ui->attrDelButton->setEnabled(false);
    ui->attrUpButton->setEnabled(false);
    ui->attrDownButton->setEnabled(false);
    ui->opeGroupBox->setEnabled(false);
    ui->opeParamDataGroupBox->setEnabled(false);
    ui->opeDelButton->setEnabled(false);
    ui->opeUpButton->setEnabled(false);
    ui->opeDownButton->setEnabled(false);
    ui->opeParamDelButton->setEnabled(false);
    ui->opeParamUpButton->setEnabled(false);
    ui->opeParamDownButton->setEnabled(false);
  }

  void				ComplexPropertyWindow::show(Object::Complex_ *complex)
  {
    clearAll();
    if ((complex_ = complex) != NULL)
      {
	ui->name->setText(complex->title_.c_str());
	ui->isAbstract->setCheckState(static_cast<Qt::CheckState>(static_cast<int>(complex->isAbstract_) * 2));
	ui->isAttrVisible->setCheckState(static_cast<Qt::CheckState>(static_cast<int>(complex->getAttrVisible()) * 2));
	ui->isOpeVisible->setCheckState(static_cast<Qt::CheckState>(static_cast<int>(complex->getOpeVisible()) * 2));
	std::list<Object::Members::Attribute *>::const_iterator it = complex->attributes_.begin();
	MemberListItem *item;
	for (; it != complex->attributes_.end(); ++it)
	  {
	    item = new MemberListItem((*it)->toString().c_str(),
				      new Object::Members::Attribute(true),
				      *it);
	    *(static_cast<Object::Members::Attribute *>(item->tmpMember_)) = *(*it);
	    ui->attrList->addItem(item);
	  }
	if (complex->attributes_.size())
	  {
	    ui->attrGroupBox->setEnabled(true);
	    ui->attrDelButton->setEnabled(true);
	    ui->attrName->setFocus(Qt::OtherFocusReason);
	    ui->attrList->setCurrentItem(ui->attrList->item(0));
	  }
      }
    else
      ui->name->setText("Test");

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

  void				ComplexPropertyWindow::clearOpeData()
  {
    ui->opeName->clear();
    ui->opeType->clear();
    ui->opeVisibility->setCurrentIndex(0);
    ui->opeParamName->clear();
    ui->opeParamType->clear();
    ui->opeParamValue->clear();
    ui->opeParamList->clear();
  }
  // !PRIVATE FUNCTION
}
