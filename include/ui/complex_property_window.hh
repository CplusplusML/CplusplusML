#ifndef		_CPLUSPLUSML_UI_COMPLEX_PROPERTY_WINDOW_HH_
# define	_CPLUSPLUSML_UI_COMPLEX_PROPERTY_WINDOW_HH_

# include	"ui_ComplexProperty.h"

namespace			CplusplusML
{
  class				ComplexPropertyWindow: public QDialog
  {
    Q_OBJECT

  public:
    ComplexPropertyWindow();
    ~ComplexPropertyWindow();

    void			show();
    void			clearAll();

  signals:
    void			applied();

  private slots:
    void			checkApply(QAbstractButton *button);
    // Attributes slots
    void			createAttr();
    void			deleteAttr();
    void			updateAttrListItem();
    // Operations slots
    void			createNewOpe();
    void			createNewOpeParam();

  public:
    Ui::ComplexProperty		*ui;

  private:
    void			clearAttrData();
  };
}

#endif		// _CPLUSPLUSML_UI_COMPLEX_PROPERTY_WINDOW_HH_
