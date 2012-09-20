#ifndef _DEPENDENCY_H_
#define _DEPENDENCY_H_

#include "arrow.hh"
#include "complex.hh"

namespace Object
{
  class Dependency : public Arrow_
  {
  public:
    Dependency() {}

    virtual ~Dependency() { }
  private:
    QGraphicsItem *Head();
  };
}

#endif /* _DEPENDENCY_H_ */
