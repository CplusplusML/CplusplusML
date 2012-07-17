#include "object/complex.hh"

void Object::Complex_::Render(void)
{
  QLabel *titleLabel = new QLabel(title_.c_str());
  // titleLabel->setFixedWidth(200);
  titleLabel->setAlignment( Qt::AlignCenter );
  titleLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
  QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
  proxy->setWidget(titleLabel);
  titleLabel->setMinimumWidth(240);

  titleLabel->setFixedWidth(titleLabel->width() + 40);

  double width = titleLabel->width();
  double height = 125;

  x_ = proxy->x() - width / 2;
  y_ = proxy->y() - height / 2;

  proxy->setX(x_);
  proxy->setY(y_);

  QGraphicsPolygonItem *polygon;
  {
    QRect titleBox(x_, y_, width, 25);
    polygon = new QGraphicsPolygonItem(static_cast<const QRectF &>(titleBox));
    polygon->setFillRule(Qt::OddEvenFill);
    polygon->setBrush(QColor(250, 250, 250));
  }
  QGraphicsPolygonItem *polygon2;
  {
    QRect titleBox(x_, y_ + 25, width, 50);
    polygon2 = new QGraphicsPolygonItem(static_cast<const QRectF &>(titleBox));
    polygon2->setFillRule(Qt::OddEvenFill);
    polygon2->setBrush(QColor(250, 250, 250));
  }
  QGraphicsPolygonItem *polygon3;
  {
    QRect titleBox(x_, y_ + 75, width, 50);
    polygon3 = new QGraphicsPolygonItem(static_cast<const QRectF &>(titleBox));
    polygon3->setFillRule(Qt::OddEvenFill);
    polygon3->setBrush(QColor(250, 250, 250));
  }

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

