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
      name = ui.name->text().toStdString();
      isAbstract = ui.isAbstract->checkState();
      isAttrVisible = ui.isAttrVisible->checkState();
      isOpeVisible = ui.isOpeVisible->checkState();

      // Erase deleted attributes
      for (auto it = attributes.begin(); it != attributes.end();)
        {
          if ((*it)->deleted)
            delete *it;
          it = attributes.erase(it);
        }

      // Erase deleted operations
      for (auto it = operations.begin(); it != operations.end();)
        {
          if ((*it)->deleted)
            delete *it;
          it = operations.erase(it);
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
          attributes.push_back(attr);
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
          operations.push_back(ope);
        }
    }
  }
}
