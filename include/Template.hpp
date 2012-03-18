
#ifndef TEMPLATE_HPP_
# define TEMPLATE_HPP_

# include <string>
# include <loki/Typelist.h>

namespace AST
{
  class Template
  {
  public:
    struct Type
    {
      Type()
      {}

      Type(const std::string &name) : _name(name)
      {}

      ~Type()
      {}

    private:
      std::string _name;
    };

    // template <typename T>
    struct TypeNumeric
    {
      TypeNumeric()
      {}

      TypeNumeric(const std::string &name) : _name(name)
      {
	// static_assert(Loki::TL::IndexOf<AuthorizedTemplates::Result, T>::value != -1, "Invalid template parameter");
      }

      ~TypeNumeric()
      {}

    private:
      typedef Loki::TL::MakeTypelist<int, long> AuthorizedNumericTypes;
      std::string _name;
    };

    struct Variadic
    {
      Variadic()
      {}

      Variadic(const std::string &name) : _name(name)
      {}

      ~Variadic()
      {}

    private:
      std::string _name;
    };
  };

  class Templateable
  {
    typedef Loki::TL::MakeTypelist<Template::Type,
				   Template::Variadic,
				   Template::TypeNumeric>
    AuthorizedTemplates;
  public:
    template <typename T, typename ...Rest>
    void Templates(const T &t, const Rest&... rest)
    {
      Templates(t);
      Templates(rest...);
    }

    template <typename T>
    void Templates(const T &t)
    {
      static_assert(Loki::TL::IndexOf<AuthorizedTemplates::Result, T>::value != -1, "Invalid template parameter");
      _templates.push_back(t);
    }

  private:
    std::vector<boost::variant<Template::Type, Template::Variadic, Template::TypeNumeric> > _templates;
  };

}

#endif	// !TEMPLATE_HPP_
