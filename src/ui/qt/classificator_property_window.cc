#include        "ui/qt/classificator_property_window.hh"
#include        "object/classificator.hh"

namespace               CplusplusML
{
  namespace             Ui
  {
    namespace           Qt
    {
      using namespace   Object::Members;

      // CTORS
      ClassificatorPropertyWindow::ClassificatorPropertyWindow():
        ui(new ::Ui::ClassificatorProperty),
        classificator_(NULL)
      {
        ui->setupUi(this);

        // Connection for apply button
        connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton *)),
                this, SLOT(CheckApply_(QAbstractButton *)));
        // Connections for attributes
        //   Buttons
        connect(ui->attrNewButton, SIGNAL(clicked()),
                this, SLOT(CreateAttr_()));
        connect(ui->attrDelButton, SIGNAL(clicked()),
                this, SLOT(DeleteAttr_()));
        connect(ui->attrUpButton, SIGNAL(clicked()),
                this, SLOT(MoveUpAttrItem_()));
        connect(ui->attrDownButton, SIGNAL(clicked()),
                this, SLOT(MoveDownAttrItem_()));
        //   Edition
        connect(ui->attrName, SIGNAL(editingFinished()),
                this, SLOT(UpdateAttrListItem_()));
        connect(ui->attrType, SIGNAL(editingFinished()),
                this, SLOT(UpdateAttrListItem_()));
        connect(ui->attrValue, SIGNAL(editingFinished()),
                this, SLOT(UpdateAttrListItem_()));
        connect(ui->attrVisibility, SIGNAL(activated(int)),
                this, SLOT(UpdateAttrListItem_()));
        connect(ui->attrIsStatic, SIGNAL(stateChanged(int)),
                this, SLOT(UpdateAttrListItem_()));
        connect(ui->attrList, SIGNAL(currentItemChanged(QListWidgetItem *,
                                                        QListWidgetItem *)),
                this, SLOT(UpdateAttrData_()));
        // Connection for operations
        //   Buttons
        //     Operations
        connect(ui->opeNewButton, SIGNAL(clicked()),
                this, SLOT(CreateOpe_()));
        connect(ui->opeDelButton, SIGNAL(clicked()),
                this, SLOT(DeleteOpe_()));
        connect(ui->opeUpButton, SIGNAL(clicked()),
                this, SLOT(MoveUpOpeItem_()));
        connect(ui->opeDownButton, SIGNAL(clicked()),
                this, SLOT(MoveDownOpeItem_()));
        //     Parameters
        connect(ui->opeParamNewButton, SIGNAL(clicked()),
                this, SLOT(CreateOpeParam_()));
        connect(ui->opeParamDelButton, SIGNAL(clicked()),
                this, SLOT(DeleteOpeParam_()));
        connect(ui->opeParamUpButton, SIGNAL(clicked()),
                this, SLOT(MoveUpOpeParamItem_()));
        connect(ui->opeParamDownButton, SIGNAL(clicked()),
                this, SLOT(MoveDownOpeParamItem_()));
        //   Edition
        //     Operations
        connect(ui->opeName, SIGNAL(editingFinished()),
                this, SLOT(UpdateOpeListItem_()));
        connect(ui->opeType, SIGNAL(editingFinished()),
                this, SLOT(UpdateOpeListItem_()));
        connect(ui->opeVisibility, SIGNAL(activated(int)),
                this, SLOT(UpdateOpeListItem_()));
        connect(ui->opeInheritance, SIGNAL(activated(int)),
                this, SLOT(UpdateOpeListItem_()));
        connect(ui->opeIsStatic, SIGNAL(stateChanged(int)),
                this, SLOT(UpdateOpeListItem_()));
        connect(ui->opeIsConst, SIGNAL(stateChanged(int)),
                this, SLOT(UpdateOpeListItem_()));
        connect(ui->opeList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
                this, SLOT(UpdateOpeData_()));
        //     Parameters
        connect(ui->opeParamName, SIGNAL(editingFinished()),
                this, SLOT(UpdateOpeParamListItem_()));
        connect(ui->opeParamType, SIGNAL(editingFinished()),
                this, SLOT(UpdateOpeParamListItem_()));
        connect(ui->opeParamValue, SIGNAL(editingFinished()),
                this, SLOT(UpdateOpeParamListItem_()));
        connect(ui->opeParamList, SIGNAL(currentItemChanged(QListWidgetItem *,
                                                            QListWidgetItem *)),
                this, SLOT(UpdateOpeParamData_()));
        connect(this, SIGNAL(UpdateOpeAndParam()),
                this, SLOT(UpdateOpeListItem_()));
    
      }
      // !CTORS

      // DTORS
      ClassificatorPropertyWindow::~ClassificatorPropertyWindow()
      {
        delete ui;
      }
      // !DTORS

      // PRIVATE SLOTS
      // ATTRIBUTES
      void              ClassificatorPropertyWindow::CheckApply_(QAbstractButton *button)
      {
        if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Apply ||
            ui->buttonBox->standardButton(button) == QDialogButtonBox::Ok)
          emit Applied();
      }

      void              ClassificatorPropertyWindow::MoveUpAttrItem_()
      {
        int             currentRow = ui->attrList->currentRow();

        if (currentRow <= 0)
          return;

        QListWidgetItem *currentItem = ui->attrList->takeItem(currentRow);
        ui->attrList->insertItem(currentRow - 1, currentItem);
        ui->attrList->setCurrentRow(currentRow - 1);
        ui->attrUpButton->setEnabled(currentRow - 1 > 0);
      }

      void              ClassificatorPropertyWindow::MoveDownAttrItem_()
      {
        int             currentRow = ui->attrList->currentRow();

        if (currentRow >= ui->attrList->count() - 1)
          return;

        QListWidgetItem *currentItem = ui->attrList->takeItem(currentRow);
        ui->attrList->insertItem(currentRow + 1, currentItem);
        ui->attrList->setCurrentRow(currentRow + 1);
        ui->attrDownButton->setEnabled(currentRow + 2 < ui->attrList->count());
      }

      // Update the list view, get data from form and make a string displayed into the list item
      void              ClassificatorPropertyWindow::UpdateAttrListItem_()
      {
        MemberListItem  *item;
        Attribute       *attr;

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
        item->setText(attr->ToString().c_str());
      }

      // When the selection change, update the attribute's data from the item in the list
      void              ClassificatorPropertyWindow::UpdateAttrData_()
      {
        MemberListItem  *item;
        Attribute       *attr;

        if (ui->attrList->currentRow() < 0)
          return;

        ClearAttrData_();
        if (!(item = static_cast<MemberListItem *>(ui->attrList->currentItem())))
          return;
        attr = static_cast<Attribute *>(item->tmpMember_);
        ui->attrName->setText(attr->name.c_str());
        ui->attrType->setText(attr->type.c_str());
        ui->attrValue->setText(attr->defaultValue.c_str());
        ui->attrVisibility->setCurrentIndex(static_cast<int>(attr->visibility));
        ui->attrIsStatic->setCheckState(static_cast< ::Qt::CheckState >(static_cast<int>(attr->isStatic) * 2));
        ui->attrUpButton->setEnabled(ui->attrList->currentRow() > 0);
        ui->attrDownButton->setEnabled(ui->attrList->currentRow() + 1 < ui->attrList->count());
        ui->attrName->setFocus(::Qt::OtherFocusReason);    
      }

      void              ClassificatorPropertyWindow::CreateAttr_()
      {
        MemberListItem  *item;
    
        item = new MemberListItem("+", new Attribute());
        ClearAttrData_();
        ui->attrList->addItem(item);
        if (!ui->attrGroupBox->isEnabled())
          {
            ui->attrGroupBox->setEnabled(true);
            ui->attrDelButton->setEnabled(true);
          }
        ui->attrName->setFocus(::Qt::OtherFocusReason);
        ui->attrList->setCurrentItem(item);
        ui->attrUpButton->setEnabled(ui->attrList->currentRow() > 0);
        ui->attrDownButton->setEnabled(ui->attrList->currentRow() + 1 < ui->attrList->count());
      }

      void              ClassificatorPropertyWindow::DeleteAttr_()
      {
        int             row = ui->attrList->currentRow();
        MemberListItem  *item;

        ClearAttrData_();
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

      void              ClassificatorPropertyWindow::CreateOpe_()
      {
        MemberListItem  *item;
    
        item = new MemberListItem("+()", new Operation());
        ClearOpeData_();
        ui->opeList->addItem(item);
        if (!ui->opeGroupBox->isEnabled())
          {
            ui->opeGroupBox->setEnabled(true);
            ui->opeDelButton->setEnabled(true);
          }
        ui->opeName->setFocus(::Qt::OtherFocusReason);
        ui->opeList->setCurrentItem(item);
        ui->opeUpButton->setEnabled(ui->opeList->currentRow() > 0);
        ui->opeDownButton->setEnabled(ui->opeList->currentRow() + 1 < ui->opeList->count());
      }

      void              ClassificatorPropertyWindow::DeleteOpe_()
      {
        int             row = ui->opeList->currentRow();
        MemberListItem  *item;

        ClearOpeData_();
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

      void              ClassificatorPropertyWindow::UpdateOpeListItem_()
      {
        MemberListItem  *item;
        Operation       *ope;

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
        item->setText(ope->ToString().c_str());
      }

      void              ClassificatorPropertyWindow::MoveUpOpeItem_()
      {
        int             currentRow = ui->opeList->currentRow();

        if (currentRow <= 0)
          return;

        QListWidgetItem *currentItem = ui->opeList->takeItem(currentRow);
        ui->opeList->insertItem(currentRow - 1, currentItem);
        ui->opeList->setCurrentRow(currentRow - 1);
        ui->opeUpButton->setEnabled(currentRow - 1 > 0);
      }

      void              ClassificatorPropertyWindow::MoveDownOpeItem_()
      {
        int             currentRow = ui->opeList->currentRow();

        if (currentRow >= ui->opeList->count() - 1)
          return;

        QListWidgetItem *currentItem = ui->opeList->takeItem(currentRow);
        ui->opeList->insertItem(currentRow + 1, currentItem);
        ui->opeList->setCurrentRow(currentRow + 1);
        ui->opeDownButton->setEnabled(currentRow + 2 < ui->opeList->count());
      }

      void              ClassificatorPropertyWindow::UpdateOpeData_()
      {
        MemberListItem  *item;
        Operation       *ope;

        if (ui->opeList->currentRow() < 0)
          return;

        ClearOpeData_();
        if (!(item = static_cast<MemberListItem *>(ui->opeList->currentItem())))
          return;

        ope = static_cast<Operation *>(item->tmpMember_);
        ui->opeName->setText(ope->name.c_str());
        ui->opeType->setText(ope->type.c_str());
        ui->opeVisibility->setCurrentIndex(static_cast<int>(ope->visibility));
        ui->opeInheritance->setCurrentIndex(static_cast<int>(ope->inhType));
        ui->opeIsStatic->setCheckState(static_cast< ::Qt::CheckState >(static_cast<int>(ope->isStatic) * 2));
        ui->opeIsConst->setCheckState(static_cast< ::Qt::CheckState >(static_cast<int>(ope->isConst) * 2));
        ui->opeUpButton->setEnabled(ui->opeList->currentRow() > 0);
        ui->opeDownButton->setEnabled(ui->opeList->currentRow() + 1 < ui->opeList->count());
        ui->opeParamList->blockSignals(true);
        ui->opeParamList->clear();
        ui->opeParamList->blockSignals(false);
        if (!ope->parameters.empty())
          {
            ui->opeParamList->blockSignals(true);
            for (Operation::Parameter &p : ope->parameters)
              ui->opeParamList->addItem(new QListWidgetItem(p.ToString(true).c_str()));
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
        ui->opeName->setFocus(::Qt::OtherFocusReason);
      }

      void              ClassificatorPropertyWindow::CreateOpeParam_()
      {
        QListWidgetItem *param;
        MemberListItem  *item;
        Operation       *ope;
    
        param = new QListWidgetItem(":");
        ClearOpeParamData_();
        ui->opeParamList->addItem(param);
        item = static_cast<MemberListItem *>(ui->opeList->currentItem());
        ope = static_cast<Operation *>(item->tmpMember_);
        ope->parameters.push_back(Operation::Parameter());
        if (!ui->opeParamDataGroupBox->isEnabled())
          {
            ui->opeParamDataGroupBox->setEnabled(true);
            ui->opeParamDelButton->setEnabled(true);
          }
        ui->opeParamName->setFocus(::Qt::OtherFocusReason);
        ui->opeParamList->setCurrentItem(param);
        ui->opeParamUpButton->setEnabled(ui->opeParamList->currentRow() > 0);
        ui->opeParamDownButton->setEnabled(ui->opeParamList->currentRow() + 1 < ui->opeParamList->count());
      }

      void              ClassificatorPropertyWindow::DeleteOpeParam_()
      {
        int             row = ui->opeParamList->currentRow();
        MemberListItem  *item;
        Operation       *ope;
        int             i;

        ClearOpeParamData_();
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

      void              ClassificatorPropertyWindow::UpdateOpeParamListItem_()
      {
        QListWidgetItem *item;
        MemberListItem  *opeItem;
        Operation       *ope;

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
        item->setText(param.ToString(true).c_str());
        emit UpdateOpeAndParam();
      }

      void              ClassificatorPropertyWindow::MoveUpOpeParamItem_()
      {
        MemberListItem  *opeItem;
        Operation       *ope;
        int             currentRow = ui->opeParamList->currentRow();
        Operation::Parameter    tmp;

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

      void              ClassificatorPropertyWindow::MoveDownOpeParamItem_()
      {
        MemberListItem  *opeItem;
        Operation       *ope;
        int             currentRow = ui->opeParamList->currentRow();
        Operation::Parameter    tmp;

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

      void              ClassificatorPropertyWindow::UpdateOpeParamData_()
      {
        MemberListItem  *opeItem;
        Operation       *ope;
        int             currentRow = ui->opeParamList->currentRow();

        if (!ui->opeParamList->count())
          return;

        ClearOpeParamData_();
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
        ui->opeParamName->setFocus(::Qt::OtherFocusReason);    
      }


      // !PRIVATE SLOTS

      // PUBLIC FUNCTIONS
      void              ClassificatorPropertyWindow::ClearAll()
      {
        // Attributes
        ClearAttrData_();
        ClearOpeData_();
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

      void              ClassificatorPropertyWindow::Show(Object::Classificator *classificator)
      {
        ClearAll();
        if ((classificator_ = classificator) != NULL)
          {
            ui->name->setText(classificator->name.c_str());
            ui->isAbstract->setCheckState(static_cast< ::Qt::CheckState>(static_cast<int>(classificator->isAbstract) * 2));
            ui->isAttrVisible->setCheckState(static_cast< ::Qt::CheckState >(static_cast<int>(classificator->isAttrVisible) * 2));
            ui->isOpeVisible->setCheckState(static_cast< ::Qt::CheckState >(static_cast<int>(classificator->isOpeVisible) * 2));
            auto it = classificator->attributes.begin();
            auto itEnd = classificator->attributes.end();
            MemberListItem  *item;
            for (; it != itEnd; ++it)
              {
                item = new MemberListItem((*it)->ToString().c_str(),
                                          new Attribute(),
                                          *it);
                *(static_cast<Attribute *>(item->tmpMember_)) = *(*it);
                ui->attrList->addItem(item);
              }
            if (classificator->attributes.size())
              {
                ui->attrGroupBox->setEnabled(true);
                ui->attrDelButton->setEnabled(true);
                ui->attrName->setFocus(::Qt::OtherFocusReason);
                ui->attrList->setCurrentItem(ui->attrList->item(0));
              }
            auto it2 = classificator->operations.begin();
            auto it2End = classificator->operations.end();
            for (; it2 != it2End; ++it2)
              {
                item = new MemberListItem((*it2)->ToString().c_str(),
                                          new Operation(),
                                          *it2);
                *(static_cast<Operation *>(item->tmpMember_)) = *(*it2);
                ui->opeList->addItem(item);
              }
            if (classificator->operations.size())
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
      void              ClassificatorPropertyWindow::ClearAttrData_()
      {
        ui->attrName->clear();
        ui->attrType->clear();
        ui->attrValue->clear();
        ui->attrVisibility->setCurrentIndex(0);
      }

      void              ClassificatorPropertyWindow::ClearOpeData_()
      {
        ui->opeName->clear();
        ui->opeType->clear();
        ui->opeVisibility->setCurrentIndex(0);
        ui->opeInheritance->setCurrentIndex(0);
        ClearOpeParamData_();
      }

      void              ClassificatorPropertyWindow::ClearOpeParamData_()
      {
        ui->opeParamName->clear();
        ui->opeParamType->clear();
        ui->opeParamValue->clear();
      }
      // !PRIVATE FUNCTION
    }
  }
}
