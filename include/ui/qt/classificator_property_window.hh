#ifndef		_CPLUSPLUSML_UI_CLASSIFICATOR_U_PROPERTY_U_WINDOW_HH_
# define	_CPLUSPLUSML_UI_CLASSIFICATOR_U_PROPERTY_U_WINDOW_HH_

# include	<map>

# include	"ui_ClassificatorProperty.h"
# include	"object/members.hh"

namespace			CplusplusML
{
  namespace Object
  {
    class Classificator;
  }

  class				MemberListItem: public QListWidgetItem
  {
  public:
    MemberListItem(QString const &text,
		   Object::Members::AMember *tmpMember,
		   Object::Members::AMember *member = NULL,
		   QListWidget *parent = 0):
      QListWidgetItem(text, parent),
      member_(member),
      tmpMember_(tmpMember)
    {}

    ~MemberListItem()
    { delete tmpMember_; }

    Object::Members::AMember	*member_;
    Object::Members::AMember	*tmpMember_;
  };

  class				ClassificatorPropertyWindow: public QDialog
  {
    Q_OBJECT

  public:
    ClassificatorPropertyWindow();
    ~ClassificatorPropertyWindow();

    void			Show(Object::Classificator *classificator = NULL);
    void			ClearAll();

  signals:
    void			Applied();
    void			UpdateOpeAndParam();

  private slots:
    void			CheckApply_(QAbstractButton *button);

    // Attributes slots
    void			CreateAttr_();
    void			DeleteAttr_();
    void			UpdateAttrListItem_();
    void			MoveUpAttrItem_();
    void			MoveDownAttrItem_();
    void			UpdateAttrData_();

    // Operations slots
    void			CreateOpe_();
    void			DeleteOpe_();
    void			UpdateOpeListItem_();
    void			MoveUpOpeItem_();
    void			MoveDownOpeItem_();
    void			UpdateOpeData_();

    // Operation param slots
    void			CreateOpeParam_();
    void			DeleteOpeParam_();
    void			UpdateOpeParamListItem_();
    void			MoveUpOpeParamItem_();
    void			MoveDownOpeParamItem_();
    void			UpdateOpeParamData_();

  public:
    Ui::ClassificatorProperty		*ui;

  private:
    void			ClearAttrData_();
    void			ClearOpeData_();
    void			ClearOpeParamData_();

  private:
    Object::Classificator		*classificator_;
  };
}

#endif		// _CPLUSPLUSML_UI_CLASSIFICATOR_U_PROPERTY_U_WINDOW_HH_
