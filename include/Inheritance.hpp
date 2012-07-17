
#ifndef INHERITANCE_HPP_
# define INHERITANCE_HPP_

# include "Visibility.hpp"

namespace AST
{
  class Class;

  class Inheritance
  {
  public:
    Inheritance(Class &c, Visibility v = Visibility::PRIVATE);
    ~Inheritance();

    friend bool operator==(const Inheritance &inh, const Class &c);

    friend bool operator==(const Class &c, const Inheritance &inh);

    friend std::ostream& operator<<(std::ostream &o,
				    Inheritance inh);

  private:
    // CA PUE DU CUL VENER! GO SMART POINTER!
    const Class* _class;
    Visibility _visibility;
  };
}

#endif	// !INHERITANCE_HPP_
