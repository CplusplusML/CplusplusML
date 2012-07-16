#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <list>
#include <string>
#include <iostream>

#include "basic.hh"

namespace Object
{
  class Complex : public Basic_
  {
  public:
    Complex() { }
    virtual ~Complex() { }
    void Render(QGraphicsScene &scene);
  private:
    virtual char Label_() = 0;
    std::string title_;
  };
}

#endif /* _COMPLEX_H_ */
