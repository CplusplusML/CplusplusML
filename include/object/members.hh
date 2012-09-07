#ifndef		_CPLUSPLUSML_MEMBERS_HH_
# define	_CPLUSPLUSML_MEMBERS_HH_

# include	<list>
# include	<map>

# include	<QtCore/QString>
# include	<QtGui/QLabel>


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
      Attribute(Complex_ *parent = NULL);
      ~Attribute();

      inline void		updateLabel(void)
      {
	label->setText(this->toString());
      }

      QString			toString(void) const;

      QString			name;
      QString			type;
      QString			defaultValue;
      Visibility		visibility;
      bool			isStatic;

      QLabel			*label;

    private:
      Complex_			*parent_;
    };

    struct			Operation
    {
      enum			InheritanceType
	{
	  LEAF,
	  VIRTUAL,
	  PURE
	};

      Operation(Complex_ *parent = NULL);
      ~Operation();

      inline void		updateLabel(void)
      {
	label->setText(this->toString());
      }

      QString			toString(void) const;

      QString			name;
      QString			type;
      Visibility		visibility;
      bool			isStatic;
      bool			isConst;
      InheritanceType		inhType;

      QLabel			*label;

      // Structure for parameters
      struct			Parameter
      {
	Parameter(Operation *parent);
	~Parameter();

	QString			toString(void) const;

	QString			name;
	QString			type;
	QString			defValue;

      private:
	Operation		*parent_;
      };
	
      std::list<Parameter *>	parameters;

    private:
      Complex_			*parent_;
    };
  }
}

#endif		// _CPLUSPLUSML_MEMBERS_HH_
