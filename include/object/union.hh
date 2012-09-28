#ifndef         _CPLUSPLUSML_OBJECT_UNION_HH_
# define        _CPLUSPLUSML_OBJECT_UNION_HH_

# include       "classificator.hh"

namespace               CplusplusML
{
  namespace             Object
  {
    // Union object
    class               Union : public Classificator
    {
    public:
      Union();
      ~Union() { }
    };
  }
}

#endif // _CPLUSPLUSML_OBJECT_UNION_HH_
