#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <list>
#include <string>
#include <iostream>

#include "basic.hh"

namespace Object
{
  class Complex_ : public Basic_
  {
  public:
    Complex_() { }
    virtual ~Complex_() { }
    void Render(QGraphicsScene &scene);
  private:
    virtual char Label_() = 0;
    std::string title_;
  };
}

#endif /* _COMPLEX_H_ */
