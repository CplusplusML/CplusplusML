#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <set>
#include <string>
#include <iostream>

#include "basic.hh"

namespace Object
{
  class Arrow_;

  class Complex_ : public Basic_
  {
  public:

    Complex_() { Render(); }
    virtual     ~Complex_() { }

    void        Render(void);
    void        AddArrow(Arrow_ *arrow);
    void        RemoveArrow(Arrow_ *arrow);
    int         X() const { return x_; }
    int         Y() const { return y_; }
  private:
    virtual char        Label_() = 0;

    std::string         title_;
    std::set<Arrow_*>   arrows_;
    int x_;
    int y_;
  };
}

#endif /* _COMPLEX_H_ */
