#include "object/arrow.hh"

void Object::Arrow_::Render(void)
{
	QGraphicsLineItem *line = new QGraphicsLineItem(
                                                  startPoint_.x(),
                                                  startPoint_.y(),
                                                  endPoint_.x(),
                                                  endPoint_.y() );
  this->addToGroup(line);
  // std::cout << "start (" << start_.x() << "," << start_.y() << ")" << std::endl;
  // std::cout << "end (" << end_.x() << "," << end_.y() << ")" << std::endl;
}


// void Object::Arrow_::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
//                   QWidget *)
// {
// }

// QRectF Object::Arrow_::boundingRect() const
// {
//   // qreal extra = (pen().width() + 20) / 2.0;

//   // return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
//   //                                   line().p2().y() - line().p1().y()))
//   //   .normalized()
//   //   .adjusted(-extra, -extra, extra, extra);

//   return QRectF(0, 0, 250, 2500);
// }
