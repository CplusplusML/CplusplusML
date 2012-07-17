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
           Complex_ &end) : start_(start), end_(end)
    {
      start.AddArrow(this);
      end.AddArrow(this);
    }

    virtual ~Arrow_() { }
    void Render(QGraphicsScene &scene);
  private:
    virtual QGraphicsItem *Head() = 0;
    Complex_ &start_;
    Complex_ &end_;

  };
}

#endif /* _ARROW_H_ */
