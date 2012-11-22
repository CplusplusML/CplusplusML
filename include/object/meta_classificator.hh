#ifndef         _CPLUSPLUSML_OBJECT_META_U_CLASSIFICATOR_HH_
# define        _CPLUSPLUSML_OBJECT_META_U_CLASSIFICATOR_HH_

# include       "classificator.hh"

namespace               CplusplusML
{
  namespace             Object
  {
    // Template parameter object
    class               MetaClassificator: public Classificator
    {
    public:
      MetaClassificator();
      ~MetaClassificator() {}
    };
  }
}

#endif          // _CPLUSPLUSML_OBJECT_META_U_CLASSIFICATOR_HH_
