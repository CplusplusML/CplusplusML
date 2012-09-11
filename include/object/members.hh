#ifndef		_CPLUSPLUSML_MEMBERS_HH_
# define	_CPLUSPLUSML_MEMBERS_HH_

# include	<list>
# include	<string>
# include	<map>

# include	<QString>
# include	<QLabel>
# include	<QGraphicsProxyWidget>
# include	<QListWidgetItem>


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

    struct			AMember
    {
      AMember();
      virtual ~AMember();

      inline void		updateLabel(void)
      {
	label->setText(this->toString().c_str());
      }

      virtual std::string	toString(void) const = 0;

      std::string		name;
      std::string		type;
      Visibility		visibility;
      bool			isStatic;

      // Qt
      QLabel			*label;
      QGraphicsProxyWidget	*labelProxy;
      bool			deleted;
    };

    struct			Attribute: public AMember
    {
      std::string		toString(void) const;

      std::string		defaultValue;
    };

    struct			Operation: public AMember
    {
      enum			InheritanceType
	{
	  LEAF,
	  VIRTUAL,
	  PURE
	};

      Operation();

      std::string		toString(void) const;

      bool			isConst;
      InheritanceType		inhType;

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
