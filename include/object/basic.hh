#ifndef _BASIC_H_
#define _BASIC_H_

#include <QGraphicsItem>

namespace Object
{
  // TODO: Change this to a class enum (c++11), and remove 'object' prefix
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
    virtual void Render(void) = 0;
  };
}


#endif /* _BASIC_H_ */
