#ifndef         _CPLUSPLUSML_OBJECT_MEMBERS_HH_
# define        _CPLUSPLUSML_OBJECT_MEMBERS_HH_

# include       <list>
# include       <string>
# include       <map>

namespace               CplusplusML
{
  namespace             Object
  {
    namespace           Members
    {
      // Visibility utilities
      enum              Visibility
        {
          PUBLIC = 0,
          PROTECTED = 1,
          PRIVATE = 2,
          UNKNOWN
        };

      inline const char *VisibilityName(Visibility v)
      {
        static std::map<Visibility, char const *>	visibilities = {
          {PUBLIC, "+"},
          {PROTECTED, "#"},
          {PRIVATE, "-"}
        };

        return (visibilities[v]);
      };

      // AMember
      struct                    AMember
      {
        AMember():
          visibility(PUBLIC),
          isStatic(false),
          deleted(false)
        {
        }

        virtual ~AMember()
        {
        }

        void                    operator=(AMember const &m);

        virtual std::string     ToString(void) const = 0;

        std::string             name;
        std::string             type;
        Visibility              visibility;
        bool                    isStatic;
        bool                    deleted;
      };

      // Attribute
      struct              Attribute: public AMember
      {
        void              operator=(Attribute const &a);
        std::string       ToString(void) const;

        std::string       defaultValue;
      };

      // Operation
      struct              Operation: public AMember
      {
        enum              InheritanceType
          {
            LEAF,
            VIRTUAL,
            PURE
          };

        Operation():
          isConst(false),
          inhType(LEAF)
        {
        }

        void              operator=(Operation const &o);
        std::string       ToString(void) const;

        bool              isConst;
        InheritanceType   inhType;

        // Structure for parameters
        struct            Parameter
        {
          std::string     ToString(bool inList = false) const;

          std::string     name;
          std::string     type;
          std::string     defValue;
        };
	
        std::list<Parameter>      parameters;
      };

      typedef std::list<Attribute *>    attrList;
      typedef std::list<Operation *>    opeList;
    }
  }
}

#endif		// _CPLUSPLUSML_OBJECT_MEMBERS_HH_
