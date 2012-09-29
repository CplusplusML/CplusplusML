#include        "ui/qt/classificator_property_window.hh"
#include        "object/classificator.hh"

namespace               CplusplusML
{
  namespace             Object
  {
    using namespace     Members;

    void                Classificator::UpdateFromForm(::Ui::ClassificatorProperty const &ui)
    {
      using ::CplusplusML::Ui::Qt::MemberListItem;

      MemberListItem    *item;
      Attribute         *attr;
      Operation         *ope;

      // Get informations
      name_ = ui.name->text().toStdString();
      isAbstract_ = ui.isAbstract->checkState();
      isAttrVisible_ = ui.isAttrVisible->checkState();
      isOpeVisible_ = ui.isOpeVisible->checkState();

      // Erase deleted attributes
      for (auto it = attributes_.begin(); it != attributes_.end();)
        {
          if ((*it)->deleted)
            delete *it;
          it = attributes_.erase(it);
        }

      // Erase deleted operations
      for (auto it = operations_.begin(); it != operations_.end();)
        {
          if ((*it)->deleted)
            delete *it;
          it = operations_.erase(it);
        }

      // For each attribute, push it in attr list
      for (int i = 0; i < ui.attrList->count(); ++i)
        {
          item = static_cast<MemberListItem *>(ui.attrList->item(i));
          attr = item->member_ ?
            static_cast<Attribute *>(item->member_) :
            new Attribute;
          *attr = *(static_cast<Attribute *>(item->tmpMember_));
          if (!item->member_)
            item->member_ = attr;
          attributes_.push_back(attr);
        }

      // For each operation, push it in attr list, updateLabel and get width
      for (int i = 0; i < ui.opeList->count(); ++i)
        {
          item = static_cast<MemberListItem *>(ui.opeList->item(i));
          ope = item->member_ ?
            static_cast<Operation *>(item->member_) :
            new Operation;
          *ope = *(static_cast<Operation *>(item->tmpMember_));
          if (!item->member_)
            item->member_ = ope;
          operations_.push_back(ope);
        }
    }
  }
}
