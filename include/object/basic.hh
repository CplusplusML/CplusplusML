#ifndef _BASIC_H_
#define _BASIC_H_

#include <QGraphicsItem>

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

  class Basic_ : public QGraphicsItemGroup
  {
  public:
    Basic_() { }
    virtual ~Basic_() { }
  };
}


#endif /* _BASIC_H_ */
