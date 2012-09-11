#include	<iostream> //DEBUG

#include	"object/members.hh"

namespace				Object
{
  namespace				Members
  {
    // AMember

    AMember::AMember():
      visibility(PUBLIC),
      isStatic(false),
      label(new QLabel()),
      labelProxy(new QGraphicsProxyWidget()),
      deleted(false)
    {
      label->setAlignment(Qt::AlignLeft);
      label->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"
					     "margin: 2 0;"));
      labelProxy->setWidget(label);
      std::cerr << "pwet" << std::endl; //DEBUG
    }

    AMember::~AMember()
    {
      delete labelProxy;
    }

    //Attribute

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

      label->setText(text.c_str());
      return (text);
    }

    // Operation

    Operation::Operation():
      isConst(false),
      inhType(LEAF)
    {
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
