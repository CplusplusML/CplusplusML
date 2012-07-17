#ifndef _UNION_H_
#define _UNION_H_

#include "complex.hh"

namespace Object
{
  class Union : public Complex_
  {
  public:
    Union() { }
    ~Union() { }
    char Label_();
  };
}

#endif /* _UNION_H_ */
