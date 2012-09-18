#ifndef		_CPLUSPLUSML_UI_PROPERTY_WINDOW_HH_
# define	_CPLUSPLUSML_UI_PROPERTY_WINDOW_HH_

# include	"ui_Property.h"

namespace			CplusplusML
{
  class			PropertyWindow: public QDialog
  {
    Q_OBJECT

  public:
    PropertyWindow();
    ~PropertyWindow();

    void		clearAll();
    void		show();

  signals:
    void		applied();

  private slots:
    void		checkApply(QAbstractButton *button);
    void		addFunc();
    void		addProp();

  public:
    Ui::Property	*ui;
  };
}

#endif		// _CPLUSPLUSML_UI_PROPERTY_WINDOW_HH_
