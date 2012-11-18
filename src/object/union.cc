#include "object/union.hh"

namespace               CplusplusML
{
  namespace             Object
  {
    // CTOR for Union object
    Union::Union()
    {
      type_ = Type::objectUnion;
      name = typeName = "union";
    }
  }
}
