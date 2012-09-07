#include	<iostream> //DEBUG

#include	<algorithm>
#include	"object/members.hh"

namespace				Object
{
  namespace				Members
  {
    //Attribute

    Attribute::Attribute(Complex_ *parent):
      visibility(PUBLIC),
      isStatic(false),
      label(new QLabel()),
      parent_(parent)
    {
    }

    Attribute::~Attribute()
    {
      std::cerr << "Deleting attribute : " << this << std::endl; //DEBUG
      delete label;
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

    Operation::Operation(Complex_ *parent):
      visibility(PUBLIC),
      isStatic(false),
      isConst(false),
      label(new QLabel()),
      parent_(parent)
    {
    }

    Operation::~Operation()
    {
      std::cerr << "Deleting operation : " << this << std::endl;
      delete label;
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
	std::list<Parameter *>::const_iterator it = parameters.begin();
	for (; it != parameters.end(); ++it)
	  {
	    if (coma)
	      {
		text += ',';
		coma = false;
	      }
	    text += (*it)->toString();
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
      return (text);
    }

    Operation::Parameter::Parameter(Operation *parent):
      parent_(parent)
    {
    }

    Operation::Parameter::~Parameter()
    {
      std::cerr << "Deleting param : " << this << std::endl; //DEBUG
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
