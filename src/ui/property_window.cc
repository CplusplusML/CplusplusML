#include "ui/property_window.hh"

PropertyWindow::PropertyWindow()
{
  ui.setupUi(this);
  connect(ui.addfuncbutton, SIGNAL(clicked()), this, SLOT(addFunc()));
  connect(ui.addpropbutton, SIGNAL(clicked()), this, SLOT(addProp()));
  connect(ui.buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(checkApply(QAbstractButton*)));
}

PropertyWindow::~PropertyWindow()
{
}

void		PropertyWindow::addFunc()
{
  QListWidgetItem	*item;

  if (!ui.addfuncedit->text().isEmpty())
    {
      item = new QListWidgetItem(ui.addfuncedit->text());
      item->setFlags(item->flags() | Qt::ItemIsEditable);
      ui.funcedit->addItem(item);
      ui.addfuncedit->clear();
    }
}

void		PropertyWindow::addProp()
{
  QListWidgetItem	*item;

  if (!ui.addpropedit->text().isEmpty())
    {
      item = new QListWidgetItem(ui.addpropedit->text());
      item->setFlags(item->flags() | Qt::ItemIsEditable);
      ui.propedit->addItem(item);
      ui.addpropedit->clear();
    }
}

void		PropertyWindow::checkApply(QAbstractButton *button)
{
  if (ui.buttonBox->standardButton(button) == QDialogButtonBox::Apply ||
      ui.buttonBox->standardButton(button) == QDialogButtonBox::Ok)
    emit applied();
}

void		PropertyWindow::show()
{
  // Clear before showing
  ui.funcedit->clear();
  ui.propedit->clear();
  ui.addfuncedit->clear();
  ui.addpropedit->clear();

  QDialog::show();
}
