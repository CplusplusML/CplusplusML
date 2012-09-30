#ifndef         _CPLUSPLUSML_OBJECT_CLASSIFICATOR_HH_
# define        _CPLUSPLUSML_OBJECT_CLASSIFICATOR_HH_

# include       <string>

# include       "ui/qt/classificator_property_window.hh"

# include       "basic.hh"
# include       "members.hh"
//# include       "arrow_connection.hh"

namespace                       CplusplusML
{
  namespace                     Object
  {
    // class                       Arrow_;
    // class                       ArrowConnection;

    class                       Classificator : public Basic
    {
    public:

      // CTORS/DTORS
      Classificator():
        isAbstract(false),
        isAttrVisible(true),
        isOpeVisible(true)
      {
      }
        
      virtual ~Classificator() {}

      // Update data from form
      void                      UpdateFromForm(::Ui::ClassificatorProperty const &ui);

      // Attributes of classificator
      std::string               typeName;
      std::string               name;
      bool                      isAbstract;
      Members::attrList         attributes;
      Members::opeList          operations;
      bool                      isAttrVisible;
      bool                      isOpeVisible;
    };
  }
}

#endif // _CPLUSPLUSML_OBJECT_CLASSIFICATOR_HH_
