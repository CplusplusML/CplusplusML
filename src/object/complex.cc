#include        <iostream> //DEBUG
#include        "object/complex.hh"

Object::Complex_::~Complex_()
{
}

void                    Object::Complex_::Render(void)
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
  //  this->addToGroup(titleLabel_);
  this->setFlag(QGraphicsItem::ItemIsMovable, true);
}

void                    Object::Complex_::AddArrow(Arrow_ *arrow)
{
  arrows_.insert(arrow);
}

void                    Object::Complex_::RemoveArrow(Arrow_ *arrow)
{
  arrows_.erase(arrow);
}

void                    Object::Complex_::updateFromForm(CplusplusML::ComplexPropertyWindow const &properties)
{
  int                   attrRows;
  int                   opeRows;
  int                   i;
  CplusplusML::MemberListItem   *item;
  Object::Members::Attribute    *attr;
  Object::Members::Operation    *ope;
  std::list<Members::Attribute *>::iterator     attrIt;
  std::list<Members::Operation *>::iterator     opeIt;

  titleLabel_->setText(properties.ui->name->text());
  int                   width = titleLabel_->boundingRect().width();
  int                   height = titleLabel_->boundingRect().height() + 4;

  // Get informations
  title_ = properties.ui->name->text().toStdString();
  isAbstract_ = properties.ui->isAbstract->checkState();
  isAttrVisible_ = properties.ui->isAttrVisible->checkState();
  isOpeVisible_ = properties.ui->isOpeVisible->checkState();

  // Erase deleted attributes
  for (attrIt = attributes_.begin(); attrIt != attributes_.end();)
    {
      if ((*attrIt)->deleted)
        delete *attrIt;
      attrIt = attributes_.erase(attrIt);
    }
  // Erase deleted operations
  for (opeIt = operations_.begin(); opeIt != operations_.end();)
    {
      if ((*opeIt)->deleted)
        delete *opeIt;
      opeIt = operations_.erase(opeIt);
    }
  // For each attribute, push it in attr list, updateLabel and get width
  attrRows = properties.ui->attrList->count();
  for (i = 0; i < attrRows; ++i)
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
  // For each operation, push it in attr list, updateLabel and get width
  opeRows = properties.ui->opeList->count();
  for (i = 0; i < opeRows; ++i)
    {
      item = static_cast<CplusplusML::MemberListItem *>(properties.ui->opeList->item(i));
      ope = item->member_ ?
        static_cast<Object::Members::Operation *>(item->member_) :
        new Object::Members::Operation;
      *ope = *(static_cast<Object::Members::Operation *>(item->tmpMember_));
      if (!item->member_)
        item->member_ = ope;
      operations_.push_back(ope);
      ope->label->setParentItem(opeRect_);
      ope->updateLabel();
      if (ope->label->boundingRect().width() > width)
      	width = ope->label->boundingRect().width();
    }
  // Min width 124
  if (width < 124)
    width = 124;
  // For padding
  width += 4;
  x_ = width / -2;
  removeFromGroup(titleRect_);
  titleRect_->setRect(x_, y_, width, height);
  addToGroup(titleRect_);
  titleLabel_->setPos(titleLabel_->boundingRect().width() / -2 + 2, y_ + 2);
  // Remove from group otherwise no boundingrect update
  removeFromGroup(attrRect_);
  attrRect_->setRect(x_, y_ + height, width, attrRows * height);
  // Update pos of all attributes and add to group
  for (i = 0, attrIt = attributes_.begin(); attrIt != attributes_.end(); ++attrIt, ++i)
    (*attrIt)->label->setPos(x_ + 2, y_ + (i + 1) * height + 2);
  addToGroup(attrRect_);
  // Same with operations
  removeFromGroup(opeRect_);
  opeRect_->setRect(x_, y_ + (attrRows + 1) * height, width,
                    height * opeRows);
  for (opeIt = operations_.begin(); opeIt != operations_.end(); ++opeIt, ++i)
    (*opeIt)->label->setPos(x_ + 2, y_ + (i + 1) * height + 2);
  addToGroup(opeRect_);
  // Update view
  update();
}
