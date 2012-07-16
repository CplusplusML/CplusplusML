#ifndef _BASIC_H_
#define _BASIC_H_

#include <list>
#include <string>
#include <QtGui>

namespace Object
{
  class Basic_
  {
  public:
    Basic_() { }
    virtual ~Basic_() { }
    virtual QGraphicsItem *View() = 0;
  };
}


#endif /* _BASIC_H_ */
