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
  titleLabel_->setParentItem(titleRect_);
  titleRect_->setParentItem(this);
  // Attributes rectangle
  attrRect_ = new QGraphicsRectItem(x_, y_ + titleHeight, width, titleHeight);
  attrRect_->setBrush(QColor(250, 250, 250));
  attrRect_->setParentItem(this);
  // Operations rectangle
  opeRect_ = new QGraphicsRectItem(x_, y_ + 2 * titleHeight, width, titleHeight);
  opeRect_->setBrush(QColor(250, 250, 250));
  opeRect_->setParentItem(this);

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
  CplusplusML::MemberListItem	*item;
  Object::Members::Attribute	*attr;
  //  Object::Members::Operation	*ope;
  std::list<Members::Attribute *>::iterator it;

  titleLabel_->setText(properties.ui->name->text());
  int width = titleLabel_->boundingRect().width();
  int height = titleLabel_->boundingRect().height() + 4;

  // Get informations
  title_ = properties.ui->name->text().toStdString();
  isAbstract_ = properties.ui->isAbstract->checkState();
  isAttrVisible_ = properties.ui->isAttrVisible->checkState();
  isOpeVisible_ = properties.ui->isOpeVisible->checkState();

  // Erase deleted attributes and remove from list (otherwise no update of boundingrect)
  for (it = attributes_.begin(); it != attributes_.end();)
    {
      removeFromGroup((*it)->label);
      if ((*it)->deleted)
	delete *it;
      it = attributes_.erase(it);
    }
  // For each attribute, push it in attr list, updateLabel and get width
  rows = properties.ui->attrList->count();
  for (i = 0; i < rows; ++i)
    {
      item = static_cast<CplusplusML::MemberListItem *>(properties.ui->attrList->item(i));
      attr = item->member_ ?
	static_cast<Object::Members::Attribute *>(item->member_) :
	new Object::Members::Attribute;
      *attr = *(static_cast<Object::Members::Attribute *>(item->tmpMember_));
      if (!item->member_)
	item->member_ = attr;
      attributes_.push_back(attr);
      attr->label->setParentItem(attrRect_);
      attr->updateLabel();
      if (attr->label->boundingRect().width() > width)
      	width = attr->label->boundingRect().width();
    }
  // Min width 124
  if (width < 124)
    width = 124;
  // For padding
  width += 4;
  x_ = width / -2;
  titleRect_->setRect(x_, y_, width, height);
  titleLabel_->setPos(titleLabel_->boundingRect().width() / -2 + 2, y_ + 2);
  // Remove from group otherwise no boundingrect update
  removeFromGroup(attrRect_);
  attrRect_->setRect(x_, y_ + height, width, rows * height);
  addToGroup(attrRect_);
  // Update pos of all attributes and add to group
  for (i = 0, it = attributes_.begin(); it != attributes_.end(); ++it, ++i)
    {
      (*it)->label->setPos(x_ + 2, y_ + (i + 1) * height + 2);
      addToGroup((*it)->label);
    }
  // Same with operations
  removeFromGroup(opeRect_);
  opeRect_->setRect(x_, y_ + (rows + 1) * height, width, height);
  addToGroup(opeRect_);
  // Update view
  update();
}
