#ifndef		_CPLUSPLUSML_UI_COMPLEX_PROPERTY_WINDOW_HH_
# define	_CPLUSPLUSML_UI_COMPLEX_PROPERTY_WINDOW_HH_

# include	<map>

# include	"ui_ComplexProperty.h"
# include	"object/members.hh"

namespace Object
{
  class Complex_;
}

namespace			CplusplusML
{
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

  class				ComplexPropertyWindow: public QDialog
  {
    Q_OBJECT

  public:
    ComplexPropertyWindow();
    ~ComplexPropertyWindow();

    void			show(Object::Complex_ *complex = NULL);
    void			clearAll();

  signals:
    void			applied();
    void			updateOpeAndParam();

  private slots:
    void			checkApply(QAbstractButton *button);

    // Attributes slots
    void			createAttr();
    void			deleteAttr();
    void			updateAttrListItem();
    void			moveUpAttrItem();
    void			moveDownAttrItem();
    void			updateAttrData();

    // Operations slots
    void			createOpe();
    void			deleteOpe();
    void			updateOpeListItem();
    void			moveUpOpeItem();
    void			moveDownOpeItem();
    void			updateOpeData();
    // Operation param slots
    void			createOpeParam();
    void			deleteOpeParam();
    void			updateOpeParamListItem();
    void			moveUpOpeParamItem();
    void			moveDownOpeParamItem();
    void			updateOpeParamData();

  public:
    Ui::ComplexProperty		*ui;

  private:
    void			clearAttrData();
    void			clearOpeData();
    void			clearOpeParamData();

  private:
    Object::Complex_		*complex_;
  };
}

#endif		// _CPLUSPLUSML_UI_COMPLEX_PROPERTY_WINDOW_HH_
