#ifndef         _CPLUSPLUSML_MEMBERS_HH_
# define        _CPLUSPLUSML_MEMBERS_HH_

# include       <list>
# include       <string>
# include       <map>

# include       <QGraphicsSimpleTextItem>


class                   Complex_;

namespace               Object
{
  namespace             Members
  {
    // Visibility utilities
    enum                Visibility
      {
        PUBLIC = 0,
        PROTECTED = 1,
        PRIVATE = 2,
        UNKNOWN
      };

    inline const char   *visibilityName(Visibility v)
    {
      static std::map<Visibility, char const *>	visibilities = {
        {PUBLIC, "+"},
        {PROTECTED, "#"},
        {PRIVATE, "-"}
      };

      return (visibilities[v]);
    };

    // AMember
    struct              AMember
    {
      AMember(bool tmpMember);
      virtual ~AMember();

      void              operator=(AMember const &m);
      inline void       updateLabel(void)
      {
        if (label)
          label->setText(this->toString().c_str());
      }

      virtual std::string	toString(void) const = 0;

      std::string       name;
      std::string       type;
      Visibility        visibility;
      bool              isStatic;

      // Qt
      QGraphicsSimpleTextItem   *label;
      bool              deleted;
    };

    // Attribute
    struct              Attribute: public AMember
    {
      Attribute(bool tmpMember = false);

      void              operator=(Attribute const &a);
      std::string       toString(void) const;

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

      Operation(bool tmpMember = false);

      void              operator=(Operation const &o);
      std::string       toString(void) const;

      bool              isConst;
      InheritanceType   inhType;

      // Structure for parameters
      struct            Parameter
      {
        std::string     toString(bool inList = false) const;

        std::string     name;
        std::string     type;
        std::string     defValue;
      };
	
      std::list<Parameter>      parameters;
    };
  }
}

#endif		// _CPLUSPLUSML_MEMBERS_HH_
