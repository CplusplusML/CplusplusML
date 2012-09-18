#include	<iostream> //DEBUG

#include	"object/members.hh"

namespace				Object
{
  namespace				Members
  {
    // AMember

    AMember::AMember(bool tmpMember):
      visibility(PUBLIC),
      isStatic(false),
      label(tmpMember ? NULL : new QGraphicsSimpleTextItem()),
      deleted(false)
    {
    }

    AMember::~AMember()
    {
      if (label)
	delete label;
    }

    void				AMember::operator=(AMember const &m)
    {
      name = m.name;
      type = m.type;
      visibility = m.visibility;
      isStatic = m.isStatic;
      deleted = m.deleted;
    }
    //Attribute

    Attribute::Attribute(bool tmpMember):
      AMember(tmpMember)
    {
    }

    void				Attribute::operator=(Attribute const &a)
    {
      AMember::operator=(a);

      defaultValue = a.defaultValue;
    }

    std::string				Attribute::toString(void) const
    {
      std::string			text;

      text += visibilityName(visibility);
      if (!name.empty())
	text += name;
      if (!type.empty())
	{
	  if (!name.empty())
	    text += ": ";
	  text += type;
	}
      if (!defaultValue.empty())
	text += " = " + defaultValue;

      return (text);
    }

    // Operation

    Operation::Operation(bool tmpMember):
      AMember(tmpMember),
      isConst(false),
      inhType(LEAF)
    {
    }

    void				Operation::operator=(Operation const &o)
    {
      AMember::operator=(o);
      isConst = o.isConst;
      inhType = o.inhType;
      parameters = o.parameters;
    }

    std::string				Operation::toString(void) const
    {
      std::string			text;

      text += visibilityName(visibility);
      if (!name.empty())
	text += name;
      text += '(';
      {
	bool				coma = false;
	std::list<Parameter>::const_iterator it = parameters.begin();
	for (; it != parameters.end(); ++it)
	  {
	    if (coma)
	      {
		text += ',';
		coma = false;
	      }
	    text += it->toString();
	  }
      }
      text += ')';
      if (!type.empty())
	{
	  if (!name.empty())
	    text += ": ";
	  text += type;
	}
      if (isConst)
	text += " const";
      if (inhType == PURE)
	text += " = 0";

      label->setText(text.c_str());
      return (text);
    }

    std::string				Operation::Parameter::toString(void) const
    {
      std::string			text;

      if (!name.empty())
	text += name;
      if (!type.empty())
	{
	  if (!name.empty())
	    text += ": ";
	  text += type;
	}
      if (!defValue.empty())
	text += '=' + defValue;

      return (text);
    }
  }
}
