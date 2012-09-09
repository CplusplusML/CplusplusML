#ifndef _ARROW_H_
#define _ARROW_H_

#include "basic.hh"
#include "complex.hh"

namespace Object
{
  class Arrow_ : public Basic_
  {
  public:
    Arrow_(Complex_ &start,
           const QPointF &coord) : start_(start), endPoint_(coord)
    {
      start.AddArrow(this);

      //      std::cout << "test : " << (start.boundingRect().x()  - start.boundingRect().width() / 2) << std::endl;
      startPoint_.setX(start.boundingRect().x() - start.boundingRect().width() / 2);
      startPoint_.setY(start.boundingRect().y() + start.boundingRect().height() / 2);

      // std::cout << "end x=" << end.boundingRect().x() << std::endl;
      // std::cout << "end y=" << end.boundingRect().y() << std::endl;
      // end.AddArrow(this);
    }

    virtual ~Arrow_() { }

    void Render(void);

    // QRectF boundingRect() const;
    // void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
    //                             QWidget *);

  private:
    virtual QGraphicsItem *Head() = 0;
    Complex_    &start_;
    QPointF     startPoint_;
    QPointF     endPoint_;
  };
}

#endif /* _ARROW_H_ */






