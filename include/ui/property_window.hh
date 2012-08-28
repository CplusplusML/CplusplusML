#include "ui_Property.h"

class		PropertyWindow: public QDialog
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
