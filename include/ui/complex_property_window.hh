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
    void			createNewOpe();
    void			createNewOpeParam();

  public:
    Ui::ComplexProperty		*ui;

  private:
    void			clearAttrData();

  private:
    Object::Complex_		*complex_;
  };
}

#endif		// _CPLUSPLUSML_UI_COMPLEX_PROPERTY_WINDOW_HH_
