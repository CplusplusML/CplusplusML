#ifndef		_CPLUSPLUSML_MEMBERS_HH_
# define	_CPLUSPLUSML_MEMBERS_HH_

# include	<list>
# include	<string>
# include	<map>

# include	<QString>
# include	<QLabel>
# include	<QGraphicsProxyWidget>


class Complex_;

namespace			Object
{
  namespace			Members
  {
    enum			Visibility
      {
	PUBLIC = 0,
	PROTECTED = 1,
	PRIVATE = 2,
	UNKNOWN
      };

    inline const char		*visibilityName(Visibility v)
    {
      static std::map<Visibility, char const *>	visibilities = {
	{PUBLIC, "+"},
	{PROTECTED, "#"},
	{PRIVATE, "-"}
      };

      return (visibilities[v]);
    };

    struct			Attribute
    {
      Attribute();
      ~Attribute();

      inline void		updateLabel(void)
      {
	label->setText(this->toString().c_str());
      }

      std::string		toString(void) const;

      std::string		name;
      std::string		type;
      std::string		defaultValue;
      Visibility		visibility;
      bool			isStatic;

      QLabel			*label;
      QGraphicsProxyWidget	*labelProxy;
    };

    struct			Operation
    {
      enum			InheritanceType
	{
	  LEAF,
	  VIRTUAL,
	  PURE
	};

      Operation();
      ~Operation();

      inline void		updateLabel(void)
      {
	label->setText(this->toString().c_str());
      }

      std::string		toString(void) const;

      std::string		name;
      std::string		type;
      Visibility		visibility;
      bool			isStatic;
      bool			isConst;
      InheritanceType		inhType;

      QLabel			*label;
      QGraphicsProxyWidget	*labelProxy;

      // Structure for parameters
      struct			Parameter
      {
	std::string		toString(void) const;

	std::string		name;
	std::string		type;
	std::string		defValue;
      };
	
      std::list<Parameter *>	parameters;
    };
  }
}

#endif		// _CPLUSPLUSML_MEMBERS_HH_
