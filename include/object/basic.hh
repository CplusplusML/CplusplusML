#ifndef		_CPLUSPLUSML_OBJECT_BASIC_HH_
# define	_CPLUSPLUSML_OBJECT_BASIC_HH_

namespace               CplusplusML
{
  namespace             Object
  {
    // All objects type
    enum class          Type
    {
      objectNone,
      objectCursor,
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

    // Basic object, inherited by all other objects
    class               Basic
    {
    public:
      Basic(): type_(Type::objectNone) { }
      virtual ~Basic() { }

      inline Type       GetType(void) const {
        return type_;
      }

    protected:
      Type              type_;
    };
  }
}


#endif // _CPLUSPLUSML_OBJECT_BASIC_H_
