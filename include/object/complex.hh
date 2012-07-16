#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <list>
#include <string>

#include "basic.hh"

namespace Object
{
  class Complex : public Basic_
  {
  public:
    Complex() { }
    ~Complex() { }
    virtual QGraphicsItem *View();
  private:
    virtual char Label_() = 0;
  };
}

#endif /* _COMPLEX_H_ */
