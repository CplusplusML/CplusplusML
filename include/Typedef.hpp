
#ifndef TYPEDEF_HPP_
# define TYPEDEF_HPP_

# include <string>
# include <ostream>
# include "Template.hpp"

namespace AST
{
  class Typedef
  {
  public:
    Typedef(const std::string &name, const std::string &txt);
    ~Typedef();
    const std::string& name() const;
    friend std::ostream& operator<<(std::ostream &o,
				    const Typedef &t);

  private:
    std::string name_;
    std::string txt_;
  };

  class TemplatedTypedef : public Templateable
  {
  public:
    TemplatedTypedef() = delete;

    TemplatedTypedef(const std::string &name, const std::string &txt) :
      name_(name), txt_(txt)
    {}

    ~TemplatedTypedef()
    {}

    friend std::ostream& operator<<(std::ostream &o,
				    const TemplatedTypedef &t)
    {
      o << static_cast<Templateable>(t) << std::endl;
      o << "using " << t.name_ << " = " << t.txt_ << ";";
      return (o);
    }

  private:
    std::string name_;
    std::string txt_;
  };

}

#endif	// !TYPEDEF_HPP_
