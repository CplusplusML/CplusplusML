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

  titleProxy_->setX(x_);
  titleProxy_->setY(y_);

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

