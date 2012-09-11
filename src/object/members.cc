#include	<iostream> //DEBUG

#include	"object/members.hh"

namespace				Object
{
  namespace				Members
  {
    //Attribute

    Attribute::Attribute():
      visibility(PUBLIC),
      isStatic(false),
      label(new QLabel()),
      labelProxy(new QGraphicsProxyWidget())
    {
      label->setAlignment(Qt::AlignLeft);
      label->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"
					     "margin: 1 0;"));
      labelProxy->setWidget(label);
    }

    Attribute::~Attribute()
    {
      delete labelProxy;
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

    Operation::Operation():
      visibility(PUBLIC),
      isStatic(false),
      isConst(false),
      label(new QLabel()),
      labelProxy(new QGraphicsProxyWidget())
    {
      label->setAlignment(Qt::AlignLeft);
      label->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
      labelProxy->setWidget(label);
    }

    Operation::~Operation()
    {
      delete labelProxy;
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
