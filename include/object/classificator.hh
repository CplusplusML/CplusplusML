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
        name_("Classificator"),
        isAttrVisible_(true),
        isOpeVisible_(true)
      {
      }
        
      virtual ~Classificator() {}

      // Getters/setters
      //   AttrVisible, are attributes visible ?
      inline bool               GetAttrVisible(void) const {
        return isAttrVisible_;
      }
      inline void               SetAttrVisible(bool v) {
        isAttrVisible_ = v;
      }
      //   OpeVisible, are operations visible ?
      inline bool               GetOpeVisible(void) const {
        return isOpeVisible_;
      }
      inline void               SetOpeVisible(bool v) {
        isOpeVisible_ = v;
      }
      //   IsAbtract ?
      inline bool               GetIsAbstract(void) const {
        return isAbstract_;
      }
      inline void               SetIsAbstract(bool v) {
        isAbstract_ = v;
      }
      //   Name of the classificator
      inline std::string const	&GetName(void) const {
        return name_;
      }
      inline void               SetName(std::string const &name) {
        name_ = name;
      }
      //   Attributes of the classificator
      inline Members::attrList const    &GetAttributes(void) const {
        return attributes_;
      }
      inline void               AddAttribute(Members::Attribute *attr) {
        attributes_.push_back(attr);
      }
      inline void               DelAttribute(Members::Attribute *attr) {
        attributes_.remove(attr);
      }
      inline void               DelAttributes(void) {
        for(auto attr : attributes_)
          delete attr;
        attributes_.clear();
      }
      //   Operations of the classificator
      inline Members::opeList const     &GetOperations(void) const {
        return operations_;
      }
      inline void               AddOperation(Members::Operation *attr) {
        operations_.push_back(attr);
      }
      inline void               DelOperation(Members::Operation *attr) {
        operations_.remove(attr);
      }
      inline void               DelOperations(void) {
        for (auto ope : operations_)
          delete ope;
        operations_.clear();
      }

      // Update data from form
      void                      UpdateFromForm(::Ui::ClassificatorProperty const &ui);

      // Attributes of classificator
    protected:
      std::string               name_;
      bool                      isAbstract_;
      Members::attrList         attributes_;
      Members::opeList          operations_;
      bool                      isAttrVisible_;
      bool                      isOpeVisible_;
    };
  }
}

#endif // _CPLUSPLUSML_OBJECT_CLASSIFICATOR_HH_
