#include "object/complex.hh"

void Object::Complex_::Render(void)
{
  //  QLabel *titleLabel = new QLabel(title_.c_str());
  titleLabel.setText(title_.c_str());
  // titleLabel->setFixedWidth(200);
  titleLabel.setAlignment( Qt::AlignCenter );
  titleLabel.setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
  QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
  proxy->setWidget(&titleLabel);
  titleLabel.setMinimumWidth(240);

  titleLabel.setFixedWidth(titleLabel.width() + 40);

  double width = titleLabel.width();
  double height = 125;

  x_ = proxy->x() - width / 2;
  y_ = proxy->y() - height / 2;

  proxy->setX(x_);
  proxy->setY(y_);

  QGraphicsRectItem *polygon;
  polygon = new QGraphicsRectItem(x_, y_, width, 25);
  polygon->setBrush(QColor(250, 250, 250));

  QGraphicsRectItem *polygon2;
  polygon2 = new QGraphicsRectItem(x_, y_ + 25, width, 50);
  polygon2->setBrush(QColor(250, 250, 250));

  QGraphicsRectItem *polygon3;
  polygon3 = new QGraphicsRectItem(x_, y_ + 75, width, 50);
  polygon3->setBrush(QColor(250, 250, 250));

  this->setFlag(QGraphicsItem::ItemIsMovable, true);
  this->addToGroup(polygon);
  this->addToGroup(polygon2);
  this->addToGroup(polygon3);
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

