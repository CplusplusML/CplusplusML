#include	<iostream> //DEBUG

#include	"object/members.hh"

namespace               CplusplusML
{
  namespace             Object
  {
    namespace           Members
    {
      void              AMember::operator=(AMember const &m)
      {
        name = m.name;
        type = m.type;
        visibility = m.visibility;
        isStatic = m.isStatic;
        deleted = m.deleted;
      }

      //Attribute
      void              Attribute::operator=(Attribute const &a)
      {
        AMember::operator=(a);

        defaultValue = a.defaultValue;
      }

      std::string       Attribute::ToString(void) const
      {
        std::string     text;

        text += VisibilityName(visibility);
        if (!type.empty())
          text += type;
        if (!name.empty())
          {
            if (!type.empty())
              text += ' ';
            text += name;
          }
        if (!defaultValue.empty())
          text += " = " + defaultValue;

        return (text);
      }

      // Operation
      void              Operation::operator=(Operation const &o)
      {
        AMember::operator=(o);
        isConst = o.isConst;
        inhType = o.inhType;
        parameters = o.parameters;
      }

      std::string       Operation::ToString(void) const
      {
        std::string     text;

        text += VisibilityName(visibility);
        if (inhType == VIRTUAL || inhType == PURE)
          text += "virtual ";
        if (!type.empty())
          text += type;
        if (!name.empty())
          {
            if (!type.empty())
              text += ' ';
            text += name;
          }
        text += '(';
        {
          bool          coma = false;
          std::list<Parameter>::const_iterator it = parameters.begin();
          for (; it != parameters.end(); ++it)
            {
              if (coma)
                text += ',';
              coma = true;
              text += it->ToString();
            }
        }
        text += ')';
        if (isConst)
          text += " const";
        if (inhType == PURE)
          text += " = 0";

        return (text);
      }

      std::string       Operation::Parameter::ToString(bool inList) const
      {
        std::string     text;

        if (!type.empty())
          text += type;
        if (!name.empty())
          {
            if (!type.empty())
              text += ' ';
            text += name;
          }
        if (!defValue.empty())
          text +=  " = " + defValue;

        if (text.empty() && inList)
          text = ':';

        return (text);
      }
    }
  }
}
