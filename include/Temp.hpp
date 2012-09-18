
#ifndef TEMP_HPP_
# define TEMP_HPP_

# include <string>
# include <boost/any.hpp>

namespace AST
{
  class Temp
  {
  public:
    Temp(const std::string &name, const std::string &txt) : name_(name), txt_(txt)
    {}

    ~Temp()
    {}

    const std::string& name() const
    {
      return (name_);
    }

    friend std::ostream& operator<<(std::ostream &o,
				    const Temp &v)
    {
      o << v.txt_ << ';' << std::endl;
      return (o);
    }

  private:
    std::string name_;
    std::string txt_;
  };

}

#endif	// !TEMP_HPP_
