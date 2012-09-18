
#ifndef TEMP_HPP_
# define TEMP_HPP_

# include <string>
# include <boost/any.hpp>

namespace AST
{
  class Temp
  {
  public:
    Temp(const std::string &name, const std::string &txt);
    ~Temp();
    const std::string& name() const;
    friend std::ostream& operator<<(std::ostream &o,
				    const Temp &v);

  private:
    std::string name_;
    std::string txt_;
  };

}

#endif	// !TEMP_HPP_
