#include <iostream>
#include "object/complex.hh"

void Object::Complex_::Render(void)
{
  titleLabel_.setText(title_.c_str());
  titleLabel_.setAlignment( Qt::AlignCenter );
  titleLabel_.setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
  QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
  proxy->setWidget(&titleLabel_);
  titleLabel_.setMinimumWidth(240);

  titleLabel_.setFixedWidth(titleLabel_.width() + 40);

  double width = titleLabel_.width();
  double height = 125;

  x_ = proxy->x() - width / 2;
  y_ = proxy->y() - height / 2;

  proxy->setX(x_);
  proxy->setY(y_ + 5);

  std::cerr << "x_ : " << x_ << std::endl;
  std::cerr << "y_ : " << y_ << std::endl;
  titleRect_.setRect(x_, y_, width, 25);
  titleRect_.setBrush(QColor(250, 250, 250));

  attrRect_.setRect(x_, y_ + 25, width, 50);
  attrRect_.setBrush(QColor(250, 250, 250));

  opeRect_.setRect(x_, y_ + 75, width, 50);
  opeRect_.setBrush(QColor(250, 250, 250));

  this->setFlag(QGraphicsItem::ItemIsMovable, true);
  this->addToGroup(&titleRect_);
  this->addToGroup(&attrRect_);
  this->addToGroup(&opeRect_);
  this->addToGroup(proxy);
}

void    Object::Complex_::AddArrow(Arrow_ *arrow)
{
  arrows_.insert(arrow);
}

void    Object::Complex_::RemoveArrow(Arrow_ *arrow)
{
  arrows_.erase(arrow);
}

