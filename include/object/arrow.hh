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
           const QPointF &coord) : start_(start)
    {
      start.AddArrow(this);
      std::cout << "start x=" << start.boundingRect().x() << std::endl;
      std::cout << "start y=" << start.boundingRect().y() << std::endl;
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
    Complex_ &start_;
  };
}

#endif /* _ARROW_H_ */
