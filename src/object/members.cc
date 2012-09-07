#include	<iostream> //DEBUG

#include	<QtCore/QStringList>
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

    QString				Attribute::toString(void) const
    {
      QString				text;

      text += visibilityName(visibility);
      if (!name.isEmpty())
	text += name;
      if (!type.isEmpty())
	{
	  if (!name.isEmpty())
	    text += ": ";
	  text += type;
	}
      if (!defaultValue.isEmpty())
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

    QString				Operation::toString(void) const
    {
      QString				text;
      QStringList			stringList;

      text += visibilityName(visibility);
      if (!name.isEmpty())
	text += name;
      text += '(';
      for (const Parameter *param: parameters)
	stringList << param->toString();
      text += stringList.join(",");
      text += ')';
      if (!type.isEmpty())
	{
	  if (!name.isEmpty())
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

    QString				Operation::Parameter::toString(void) const
    {
      QString				text;

      if (!name.isEmpty())
	text += name;
      if (!type.isEmpty())
	{
	  if (!name.isEmpty())
	    text += ": ";
	  text += type;
	}
      if (!defValue.isEmpty())
	text += '=' + defValue;

      return (text);
    }
  }
}
