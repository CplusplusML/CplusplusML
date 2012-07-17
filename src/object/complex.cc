#include "object/complex.hh"

void Object::Complex_::Render(QGraphicsScene &scene)
{
  title_ = "test";
  QLabel *titleLabel = new QLabel(title_.c_str());
  titleLabel->setFixedWidth(200);
  titleLabel->setAlignment( Qt::AlignCenter );
  titleLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
  QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
  proxy->setWidget(titleLabel);
  QGraphicsPolygonItem *polygon;
  {
    QRect titleBox(0, 0, titleLabel->width(), 25);
    polygon = new QGraphicsPolygonItem(static_cast<const QRectF &>(titleBox));
    polygon->setFillRule(Qt::OddEvenFill);
    polygon->setBrush(QColor(250, 250, 250));
  }
  QGraphicsPolygonItem *polygon2;
  {
    QRect titleBox(0, 25, titleLabel->width(), 50);
    polygon2 = new QGraphicsPolygonItem(static_cast<const QRectF &>(titleBox));
    polygon2->setFillRule(Qt::OddEvenFill);
    polygon2->setBrush(QColor(250, 250, 250));
  }
  QGraphicsPolygonItem *polygon3;
  {
    QRect titleBox(0, 75, titleLabel->width(), 50);
    polygon3 = new QGraphicsPolygonItem(static_cast<const QRectF &>(titleBox));
    polygon3->setFillRule(Qt::OddEvenFill);
    polygon3->setBrush(QColor(250, 250, 250));
  }

  QGraphicsItemGroup *group = scene.createItemGroup({polygon, proxy, polygon2, polygon3});
  group->setFlag(QGraphicsItem::ItemIsMovable, true);
}

void    Object::Complex_::AddArrow(Arrow_ *arrow)
{
  arrows_.insert(arrow);
}

void    Object::Complex_::RemoveArrow(Arrow_ *arrow)
{
  arrows_.erase(arrow);
}


void Object::Complex_::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                  QWidget *)
{
}

QRectF Object::Complex_::boundingRect() const
{
  return QRectF(0, 0, 250, 2500);
}
