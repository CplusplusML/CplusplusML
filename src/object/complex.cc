#include "object/complex.hh"

void Object::Complex::Render(QGraphicsScene &scene)
{
  QLabel *titleLabel = new QLabel(title_.c_str());
  titleLabel->setFixedWidth(200);
  titleLabel->setAlignment( Qt::AlignCenter );
  titleLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
  QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
  proxy->setWidget(titleLabel);
  QRect titleBox(0, 0, titleLabel->width(), 50);
  QGraphicsPolygonItem *polygon = new QGraphicsPolygonItem(static_cast<const QRectF &>(titleBox));
  QGraphicsItemGroup *group = scene.createItemGroup({proxy, polygon});
  group->setFlag(QGraphicsItem::ItemIsMovable, true);
}
