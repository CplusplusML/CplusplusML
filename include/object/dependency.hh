#ifndef _DEPENDENCY_H_
#define _DEPENDENCY_H_

#include "arrow.hh"
#include "complex.hh"

namespace Object
{
  class Dependency_ : public Arrow_
  {
  public:
    Dependency_(Complex_ &start,
                Complex_ &end) : Arrow_(start, end)
    {  }

    virtual ~Dependency_() { }
  private:
    QGraphicsItem *Head();
  };
}

#endif /* _DEPENDENCY_H_ */
