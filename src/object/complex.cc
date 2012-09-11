#include <iostream> //DEBUG
#include "object/complex.hh"

Object::Complex_::~Complex_()
{
  // Remove from group
  this->removeFromGroup(titleProxy_);
  this->removeFromGroup(titleRect_);
  this->removeFromGroup(attrRect_);
  this->removeFromGroup(opeRect_);
  // Delete items, DO NOT DELETE label, proxy do it for you
  delete titleProxy_;
  delete titleRect_;
  delete attrRect_;
  delete opeRect_;
}

void Object::Complex_::Render(void)
{
  // Label
  titleLabel_ = new QLabel(title_.c_str());
  titleLabel_->setAlignment(Qt::AlignCenter);
  titleLabel_->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"
					       "margin: 2 0;"));
  titleLabel_->setFixedWidth(titleLabel_->width() + 40);
  titleLabel_->setMinimumWidth(240);

  // Label proxy
  titleProxy_ = new QGraphicsProxyWidget();
  titleProxy_->setWidget(titleLabel_);

  double width = titleLabel_->width();
  double titleHeight = titleLabel_->height();
  double height = titleHeight * 3;

  x_ = titleProxy_->x() - width / 2;
  y_ = titleProxy_->y() - height / 2;

  titleProxy_->setPos(x_, y_);

  // Title rectangle
  titleRect_ = new QGraphicsRectItem(x_, y_, width, titleHeight);
  titleRect_->setBrush(QColor(250, 250, 250));

  // Attributes rectangle
  attrRect_ = new QGraphicsRectItem(x_, y_ + titleHeight, width, titleHeight);
  attrRect_->setBrush(QColor(250, 250, 250));

  // Operations rectangle
  opeRect_ = new QGraphicsRectItem(x_, y_ + 2 * titleHeight, width, titleHeight);
  opeRect_->setBrush(QColor(250, 250, 250));

  // Add all items to group
  this->addToGroup(titleRect_);
  this->addToGroup(attrRect_);
  this->addToGroup(opeRect_);
  this->addToGroup(titleProxy_);
  this->setFlag(QGraphicsItem::ItemIsMovable, true);
}

void    Object::Complex_::AddArrow(Arrow_ *arrow)
{
  arrows_.insert(arrow);
}

void    Object::Complex_::RemoveArrow(Arrow_ *arrow)
{
  arrows_.erase(arrow);
}

void	Object::Complex_::updateFromForm(CplusplusML::ComplexPropertyWindow const &properties)
{
  int	rows;
  QListWidgetItem	*item;

  int width = titleLabel_->width();
  int height = titleLabel_->height();
  // Get informations
  title_ = properties.ui->name->text().toStdString();
  isAbstract_ = properties.ui->isAbstract->checkState();
  isAttrVisible_ = properties.ui->isAttrVisible->checkState();
  isOpeVisible_ = properties.ui->isOpeVisible->checkState();
  // Update labels
  titleLabel_->setText(properties.ui->name->text());
  {
    std::list<Members::Attribute *>::iterator it = attributes_.begin();
    for (;it != attributes_.end();)
      {
	removeFromGroup((*it)->labelProxy);
	if ((*it)->deleted)
	  delete *it;
	it = attributes_.erase(it);
      }
    rows = properties.attributes_.size();
    attrRect_->setRect(x_, y_ + height, width, rows * height);
    for (int i = 0; i < rows; ++i)
      {
    	item = properties.ui->attrList->item(i);
    	attributes_.push_back(properties.attributes_.find(item)->second);
	attributes_.back()->updateLabel();
    	attributes_.back()->labelProxy->setPos(x() + x_, y() + y_ + (i + 1) * height);
    	addToGroup(attributes_.back()->labelProxy);
      }
  }
  opeRect_->setRect(x_, y_ + (rows + 1) * height, width, height);
  // Update view
  update();
}
