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

                Complex_() { }
    virtual     ~Complex_() { }

    void        Render(QGraphicsScene &scene);
    void        AddArrow(Arrow_ *arrow);
    void        RemoveArrow(Arrow_ *arrow);

  private:
    virtual char        Label_() = 0;

    std::string         title_;
    std::set<Arrow_*>   arrows_;
  };
}

#endif /* _COMPLEX_H_ */
