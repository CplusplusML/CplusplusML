#include        <iostream> //DEBUG

#include        "ui/complex_property_window.hh"
#include        "object/complex.hh"

using namespace std; //DEBUG

namespace               CplusplusML
{
  using namespace       Object::Members;
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
    connect(ui->opeInheritance, SIGNAL(activated(int)),
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
    connect(ui->opeParamList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(updateOpeParamData()));
    connect(this, SIGNAL(updateOpeAndParam()), this, SLOT(updateOpeListItem()));
    
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
  void          ComplexPropertyWindow::checkApply(QAbstractButton *button)
  {
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Apply ||
        ui->buttonBox->standardButton(button) == QDialogButtonBox::Ok)
      emit applied();
  }

  void          ComplexPropertyWindow::moveUpAttrItem()
  {
    int         currentRow = ui->attrList->currentRow();

    if (currentRow <= 0)
      return;

    QListWidgetItem     *currentItem = ui->attrList->takeItem(currentRow);
    ui->attrList->insertItem(currentRow - 1, currentItem);
    ui->attrList->setCurrentRow(currentRow - 1);
    ui->attrUpButton->setEnabled(currentRow - 1 > 0);
  }

  void          ComplexPropertyWindow::moveDownAttrItem()
  {
    int         currentRow = ui->attrList->currentRow();

    if (currentRow >= ui->attrList->count() - 1)
      return;

    QListWidgetItem     *currentItem = ui->attrList->takeItem(currentRow);
    ui->attrList->insertItem(currentRow + 1, currentItem);
    ui->attrList->setCurrentRow(currentRow + 1);
    ui->attrDownButton->setEnabled(currentRow + 2 < ui->attrList->count());
  }

  // Update the list view, get data from form and make a string displayed into the list item
  void                  ComplexPropertyWindow::updateAttrListItem()
  {
    MemberListItem      *item;
    Attribute           *attr;

    if (!(item = static_cast<MemberListItem *>(ui->attrList->currentItem())))
      return;
    ui->attrName->setText(ui->attrName->text().trimmed());
    ui->attrType->setText(ui->attrType->text().trimmed());
    ui->attrValue->setText(ui->attrValue->text().trimmed());

    attr = static_cast<Attribute *>(item->tmpMember_);
    attr->name = ui->attrName->text().toStdString();
    attr->type = ui->attrType->text().toStdString();
    attr->defaultValue = ui->attrValue->text().toStdString();
    attr->visibility = static_cast<Visibility>(ui->attrVisibility->currentIndex());
    attr->isStatic = ui->attrIsStatic->checkState();
    item->setText(attr->toString().c_str());
  }

  // When the selection change, update the attribute's data from the item in the list
  void                  ComplexPropertyWindow::updateAttrData()
  {
    MemberListItem      *item;
    Attribute           *attr;

    if (ui->attrList->currentRow() < 0)
      return;

    clearAttrData();
    if (!(item = static_cast<MemberListItem *>(ui->attrList->currentItem())))
      return;
    attr = static_cast<Attribute *>(item->tmpMember_);
    ui->attrName->setText(attr->name.c_str());
    ui->attrType->setText(attr->type.c_str());
    ui->attrValue->setText(attr->defaultValue.c_str());
    ui->attrVisibility->setCurrentIndex(static_cast<int>(attr->visibility));
    ui->attrIsStatic->setCheckState(static_cast<Qt::CheckState>(static_cast<int>(attr->isStatic) * 2));
    ui->attrUpButton->setEnabled(ui->attrList->currentRow() > 0);
    ui->attrDownButton->setEnabled(ui->attrList->currentRow() + 1 < ui->attrList->count());
    ui->attrName->setFocus(Qt::OtherFocusReason);    
  }

  void                  ComplexPropertyWindow::createAttr()
  {
    MemberListItem      *item;
    
    item = new MemberListItem("+", new Attribute(true));
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

  void                  ComplexPropertyWindow::deleteAttr()
  {
    int                 row = ui->attrList->currentRow();
    MemberListItem      *item;

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
    row = ui->attrList->currentRow();
    ui->attrUpButton->setEnabled(row > 0);
    ui->attrDownButton->setEnabled(row + 1 < ui->attrList->count());
  }
  
  // OPERATIONS

  void                  ComplexPropertyWindow::createOpe()
  {
    MemberListItem      *item;
    
    item = new MemberListItem("+()", new Operation(true));
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

  void                  ComplexPropertyWindow::deleteOpe()
  {
    int                 row = ui->opeList->currentRow();
    MemberListItem      *item;

    clearOpeData();
    item = static_cast<MemberListItem *>(ui->opeList->takeItem(row));
    if (item->member_)
      item->member_->deleted = true;
    delete item;
    if (!ui->opeList->count())
      {
        ui->opeGroupBox->setEnabled(false);
        ui->opeParamDataGroupBox->setEnabled(false);
        ui->opeDelButton->setEnabled(false);
        ui->opeParamDelButton->setEnabled(false);
      }
    ui->opeUpButton->setEnabled(ui->opeList->currentRow() > 0);
    ui->opeDownButton->setEnabled(ui->opeList->currentRow() + 1 < ui->opeList->count());
    ui->opeParamUpButton->setEnabled(ui->opeParamList->currentRow() > 0);
    ui->opeParamDownButton->setEnabled(ui->opeParamList->currentRow() + 1 < ui->opeParamList->count());
  }

  void                  ComplexPropertyWindow::updateOpeListItem()
  {
    MemberListItem      *item;
    Operation           *ope;

    if (!(item = static_cast<MemberListItem *>(ui->opeList->currentItem())))
      return;
    ui->opeName->setText(ui->opeName->text().trimmed());
    ui->opeType->setText(ui->opeType->text().trimmed());

    ope = static_cast<Operation *>(item->tmpMember_);
    ope->name = ui->opeName->text().toStdString();
    ope->type = ui->opeType->text().toStdString();
    ope->visibility = static_cast<Visibility>(ui->opeVisibility->currentIndex());
    ope->inhType = static_cast<Operation::InheritanceType>(ui->opeInheritance->currentIndex());
    ope->isStatic = ui->opeIsStatic->checkState();
    ope->isConst = ui->opeIsConst->checkState();
    item->setText(ope->toString().c_str());
  }

  void          ComplexPropertyWindow::moveUpOpeItem()
  {
    int         currentRow = ui->opeList->currentRow();

    if (currentRow <= 0)
      return;

    QListWidgetItem     *currentItem = ui->opeList->takeItem(currentRow);
    ui->opeList->insertItem(currentRow - 1, currentItem);
    ui->opeList->setCurrentRow(currentRow - 1);
    ui->opeUpButton->setEnabled(currentRow - 1 > 0);
  }

  void          ComplexPropertyWindow::moveDownOpeItem()
  {
    int         currentRow = ui->opeList->currentRow();

    if (currentRow >= ui->opeList->count() - 1)
      return;

    QListWidgetItem *currentItem = ui->opeList->takeItem(currentRow);
    ui->opeList->insertItem(currentRow + 1, currentItem);
    ui->opeList->setCurrentRow(currentRow + 1);
    ui->opeDownButton->setEnabled(currentRow + 2 < ui->opeList->count());
  }

  void                  ComplexPropertyWindow::updateOpeData()
  {
    MemberListItem      *item;
    Operation           *ope;

    if (ui->opeList->currentRow() < 0)
      return;

    clearOpeData();
    if (!(item = static_cast<MemberListItem *>(ui->opeList->currentItem())))
      return;

    ope = static_cast<Operation *>(item->tmpMember_);
    ui->opeName->setText(ope->name.c_str());
    ui->opeType->setText(ope->type.c_str());
    ui->opeVisibility->setCurrentIndex(static_cast<int>(ope->visibility));
    ui->opeInheritance->setCurrentIndex(static_cast<int>(ope->inhType));
    ui->opeIsStatic->setCheckState(static_cast<Qt::CheckState>(static_cast<int>(ope->isStatic) * 2));
    ui->opeIsConst->setCheckState(static_cast<Qt::CheckState>(static_cast<int>(ope->isConst) * 2));
    ui->opeUpButton->setEnabled(ui->opeList->currentRow() > 0);
    ui->opeDownButton->setEnabled(ui->opeList->currentRow() + 1 < ui->opeList->count());
    ui->opeParamList->blockSignals(true);
    ui->opeParamList->clear();
    ui->opeParamList->blockSignals(false);
    if (!ope->parameters.empty())
      {
        ui->opeParamList->blockSignals(true);
        for (Operation::Parameter &p : ope->parameters)
          ui->opeParamList->addItem(new QListWidgetItem(p.toString(true).c_str()));
        ui->opeParamList->setCurrentItem(ui->opeParamList->item(0));
        ui->opeParamName->setText(ope->parameters.front().name.c_str());
        ui->opeParamType->setText(ope->parameters.front().type.c_str());
        ui->opeParamValue->setText(ope->parameters.front().defValue.c_str());
        ui->opeParamList->blockSignals(false);
        ui->opeParamDelButton->setEnabled(true);
        ui->opeParamDataGroupBox->setEnabled(true);
      }
    else
      {
        ui->opeParamDelButton->setEnabled(false);
        ui->opeParamDataGroupBox->setEnabled(false);
      }
    ui->opeParamUpButton->setEnabled(ui->opeParamList->currentRow() > 0);
    ui->opeParamDownButton->setEnabled(ui->opeParamList->currentRow() + 1 < ui->opeParamList->count());
    ui->opeName->setFocus(Qt::OtherFocusReason);
  }

  void                  ComplexPropertyWindow::createOpeParam()
  {
    QListWidgetItem     *param;
    MemberListItem      *item;
    Operation           *ope;
    
    param = new QListWidgetItem(":");
    clearOpeParamData();
    ui->opeParamList->addItem(param);
    item = static_cast<MemberListItem *>(ui->opeList->currentItem());
    ope = static_cast<Operation *>(item->tmpMember_);
    ope->parameters.push_back(Operation::Parameter());
    if (!ui->opeParamDataGroupBox->isEnabled())
      {
        ui->opeParamDataGroupBox->setEnabled(true);
        ui->opeParamDelButton->setEnabled(true);
      }
    ui->opeParamName->setFocus(Qt::OtherFocusReason);
    ui->opeParamList->setCurrentItem(param);
    ui->opeParamUpButton->setEnabled(ui->opeParamList->currentRow() > 0);
    ui->opeParamDownButton->setEnabled(ui->opeParamList->currentRow() + 1 < ui->opeParamList->count());
  }

  void                  ComplexPropertyWindow::deleteOpeParam()
  {
    int                 row = ui->opeParamList->currentRow();
    MemberListItem      *item;
    Operation           *ope;
    int                 i;

    clearOpeParamData();
    delete ui->opeParamList->takeItem(row);
    item = static_cast<MemberListItem *>(ui->opeList->currentItem());
    ope = static_cast<Operation *>(item->tmpMember_);
    auto it = ope->parameters.begin();
    for (i = 0; i < row; ++it, ++i);
    ope->parameters.erase(it);
    if (!ui->opeParamList->count())
      {
        ui->opeParamDataGroupBox->setEnabled(false);
        ui->opeParamDelButton->setEnabled(false);
      }
    ui->opeParamUpButton->setEnabled(ui->opeParamList->currentRow() > 0);
    ui->opeParamDownButton->setEnabled(ui->opeParamList->currentRow() + 1 < ui->opeParamList->count());
  }

  void                  ComplexPropertyWindow::updateOpeParamListItem()
  {
    QListWidgetItem     *item;
    MemberListItem      *opeItem;
    Operation           *ope;

    if (!ui->opeParamList->count() || !(item = ui->opeParamList->currentItem()))
      return;

    ui->opeParamName->setText(ui->opeParamName->text().trimmed());
    ui->opeParamType->setText(ui->opeParamType->text().trimmed());
    ui->opeParamValue->setText(ui->opeParamValue->text().trimmed());
    
    opeItem = static_cast<MemberListItem *>(ui->opeList->currentItem());
    ope = static_cast<Operation *>(opeItem->tmpMember_);
    auto it = ope->parameters.begin();
    for (int i = 0; i < ui->opeParamList->currentRow(); ++it, ++i);
    Operation::Parameter	&param = *it;
    param.name = ui->opeParamName->text().toStdString();
    param.type = ui->opeParamType->text().toStdString();
    param.defValue = ui->opeParamValue->text().toStdString();
    item->setText(param.toString(true).c_str());
    emit updateOpeAndParam();
  }

  void                          ComplexPropertyWindow::moveUpOpeParamItem()
  {
    MemberListItem              *opeItem;
    Operation                   *ope;
    int                         currentRow = ui->opeParamList->currentRow();
    Operation::Parameter        tmp;

    if (currentRow <= 0)
      return;

    opeItem = static_cast<MemberListItem *>(ui->opeList->currentItem());
    ope = static_cast<Operation *>(opeItem->tmpMember_);
    auto it = ope->parameters.begin();
    for (int i = 0; i < currentRow; ++it, ++i);
    tmp = *it;
    ope->parameters.erase(it);
    it = ope->parameters.begin();
    for (int i = 0; i < currentRow - 1; ++it, ++i);
    ope->parameters.insert(it, tmp);
    QListWidgetItem     *currentItem = ui->opeParamList->takeItem(currentRow);
    ui->opeParamList->insertItem(currentRow - 1, currentItem);
    ui->opeParamList->setCurrentRow(currentRow - 1);
    ui->opeParamUpButton->setEnabled(currentRow - 1 > 0);
  }

  void                          ComplexPropertyWindow::moveDownOpeParamItem()
  {
    MemberListItem              *opeItem;
    Operation                   *ope;
    int                         currentRow = ui->opeParamList->currentRow();
    Operation::Parameter        tmp;

    if (currentRow >= ui->opeParamList->count() - 1)
      return;

    opeItem = static_cast<MemberListItem *>(ui->opeList->currentItem());
    ope = static_cast<Operation *>(opeItem->tmpMember_);
    auto it = ope->parameters.begin();
    for (int i = 0; i < currentRow; ++it, ++i);
    tmp = *it;
    ope->parameters.erase(it);
    it = ope->parameters.begin();
    for (int i = 0; i < currentRow + 1; ++it, ++i);
    ope->parameters.insert(it, tmp);
    QListWidgetItem     *currentItem = ui->opeParamList->takeItem(currentRow);
    ui->opeParamList->insertItem(currentRow + 1, currentItem);
    ui->opeParamList->setCurrentRow(currentRow + 1);
    ui->opeParamDownButton->setEnabled(currentRow + 2 < ui->opeParamList->count());
  }

  void                  ComplexPropertyWindow::updateOpeParamData()
  {
    MemberListItem      *opeItem;
    Operation           *ope;
    int                 currentRow = ui->opeParamList->currentRow();

    if (!ui->opeParamList->count())
      return;

    clearOpeParamData();
    opeItem = static_cast<MemberListItem *>(ui->opeList->currentItem());
    ope = static_cast<Operation *>(opeItem->tmpMember_);
    auto it = ope->parameters.begin();
    for (int i = 0; i < currentRow; ++it, ++i);
    Operation::Parameter        &param = *it;
    ui->opeParamName->setText(param.name.c_str());
    ui->opeParamType->setText(param.type.c_str());
    ui->opeParamValue->setText(param.defValue.c_str());
    ui->opeParamUpButton->setEnabled(currentRow > 0);
    ui->opeParamDownButton->setEnabled(currentRow + 1 < ui->opeParamList->count());
    ui->opeParamName->setFocus(Qt::OtherFocusReason);    
  }


  // !PRIVATE SLOTS

  // PUBLIC FUNCTIONS
  void          ComplexPropertyWindow::clearAll()
  {
    // Attributes
    clearAttrData();
    clearOpeData();
    ui->attrList->blockSignals(true);
    ui->attrList->clear();
    ui->attrList->blockSignals(false);
    ui->opeList->blockSignals(true);
    ui->opeList->clear();
    ui->opeList->blockSignals(false);
    ui->opeParamList->blockSignals(true);
    ui->opeParamList->clear();
    ui->opeParamList->blockSignals(false);
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

  void          ComplexPropertyWindow::show(Object::Complex_ *complex)
  {
    clearAll();
    if ((complex_ = complex) != NULL)
      {
        ui->name->setText(complex->title_.c_str());
        ui->isAbstract->setCheckState(static_cast<Qt::CheckState>(static_cast<int>(complex->isAbstract_) * 2));
        ui->isAttrVisible->setCheckState(static_cast<Qt::CheckState>(static_cast<int>(complex->getAttrVisible()) * 2));
        ui->isOpeVisible->setCheckState(static_cast<Qt::CheckState>(static_cast<int>(complex->getOpeVisible()) * 2));
        auto it = complex->attributes_.begin();
        MemberListItem  *item;
        for (; it != complex->attributes_.end(); ++it)
          {
            item = new MemberListItem((*it)->toString().c_str(),
                                      new Attribute(true),
                                      *it);
            *(static_cast<Attribute *>(item->tmpMember_)) = *(*it);
            ui->attrList->addItem(item);
          }
        if (complex->attributes_.size())
          {
            ui->attrGroupBox->setEnabled(true);
            ui->attrDelButton->setEnabled(true);
            ui->attrName->setFocus(Qt::OtherFocusReason);
            ui->attrList->setCurrentItem(ui->attrList->item(0));
          }
        auto it2 = complex->operations_.begin();
        for (; it2 != complex->operations_.end(); ++it2)
          {
            item = new MemberListItem((*it2)->toString().c_str(),
                                      new Operation(true),
                                      *it2);
            *(static_cast<Operation *>(item->tmpMember_)) = *(*it2);
            ui->opeList->addItem(item);
          }
        if (complex->operations_.size())
          {
            ui->opeGroupBox->setEnabled(true);
            ui->opeDelButton->setEnabled(true);
            ui->opeList->setCurrentItem(ui->opeList->item(0));
          }
      }

    QDialog::show();
  }
  // !PUBLIC FUNCTIONS

  // PRIVATE FUNCTION
  void          ComplexPropertyWindow::clearAttrData()
  {
    ui->attrName->clear();
    ui->attrType->clear();
    ui->attrValue->clear();
    ui->attrVisibility->setCurrentIndex(0);
  }

  void          ComplexPropertyWindow::clearOpeData()
  {
    ui->opeName->clear();
    ui->opeType->clear();
    ui->opeVisibility->setCurrentIndex(0);
    ui->opeInheritance->setCurrentIndex(0);
    clearOpeParamData();
  }

  void				ComplexPropertyWindow::clearOpeParamData()
  {
    ui->opeParamName->clear();
    ui->opeParamType->clear();
    ui->opeParamValue->clear();
  }
  // !PRIVATE FUNCTION
}
