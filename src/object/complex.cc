#include <iostream> //DEBUG
#include "object/complex.hh"

Object::Complex_::~Complex_()
{
}

void Object::Complex_::Render(void)
{
  // Label
  titleLabel_ = new QGraphicsSimpleTextItem();
  titleLabel_->setText("Test");

  double width = titleLabel_->boundingRect().width() + 4;
  if (width < 124)
    width = 124;
  double titleHeight = titleLabel_->boundingRect().height() + 4;
  double height = titleHeight * 3;

  x_ = width / -2;
  y_ = height / -2;

  titleLabel_->setPos(titleLabel_->boundingRect().width() / -2 + 2, y_ + 2);

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
  this->addToGroup(titleLabel_);
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
  int	i;
  QListWidgetItem		*item;
  Object::Members::Attribute	*attr;
  Object::Members::Operation	*ope;
  std::list<Members::Attribute *>::iterator it;

  titleLabel_->setText(properties.ui->name->text());
  int width = titleLabel_->boundingRect().width() + 4;
  int height = titleLabel_->boundingRect().height() + 4;
  // Get informations
  title_ = properties.ui->name->text().toStdString();
  isAbstract_ = properties.ui->isAbstract->checkState();
  isAttrVisible_ = properties.ui->isAttrVisible->checkState();
  isOpeVisible_ = properties.ui->isOpeVisible->checkState();
  // Update labels
  for (it = attributes_.begin(); it != attributes_.end();)
    {
      if ((*it)->deleted)
	{
	  removeFromGroup((*it)->label);
	  delete *it;
	}
      it = attributes_.erase(it);
    }
  rows = properties.attributes_.size();
  for (i = 0; i < rows; ++i)
    {
      item = properties.ui->attrList->item(i);
      attr = properties.attributes_.find(item)->second;
      attributes_.push_back(attr);
      attr->updateLabel();
      attr->label->setParentItem(attrRect_);
      if (attr->label->boundingRect().width() + 4 > width)
      	width = attr->label->boundingRect().width() + 4;
      addToGroup(attr->label);
    }
  if (width < 124)
    width = 124;
  x_ = width / -2;
  titleRect_->setRect(x_, y_, width, height);
  titleLabel_->setPos(titleLabel_->boundingRect().width() / -2 + 2, y_ + 2);
  attrRect_->setRect(x_, y_ + height, width, rows * height);
  for (i = 0, it = attributes_.begin(); it != attributes_.end(); ++it, ++i)
    (*it)->label->setPos(x_ + 2, y_ + (i + 1) * height + 2);
  opeRect_->setRect(x_, y_ + (rows + 1) * height, width, height);
  // Update view
  update();
}
