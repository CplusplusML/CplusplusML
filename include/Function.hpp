
#ifndef FUNCTION_HPP_
# define FUNCTION_HPP_

# include "Template.hpp"

namespace AST
{
  class Function : public Templateable
  {
  public:
    using Templateable::Templates;

    Function()
    {}
  };
}

#endif	// !FUNCTION_HPP_
