#include "object/meta_classificator.hh"

namespace               CplusplusML
{
  namespace             Object
  {
    // CTOR/DTORS
    MetaClassificator::MetaClassificator()
    {
      type_ = Type::objectMetaClassificator;
      name = typeName = "meta";
    }
  }
}
