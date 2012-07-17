#ifndef _BASIC_H_
#define _BASIC_H_

#include <list>
#include <string>
#include <QApplication>
#include <QtGui>

namespace Object
{
  enum ObjectType
    {
      objectCursor = 0,
      objectNamespace,
      objectClass,
      objectStruct,
      objectEnum,
      objectUnion,
      objectTypedef,
      objectAggregation,
      objectDependency,
      objectComposition,
      objectInheritance,
      objectFreeFunction,
      objectTemplate,
      objectLibrary,
      objectCount_
    };

  class Basic_
  {
  public:
    Basic_() { }
    virtual ~Basic_() { }
    virtual void Render(QGraphicsScene &scene) = 0;
  };
}


#endif /* _BASIC_H_ */
