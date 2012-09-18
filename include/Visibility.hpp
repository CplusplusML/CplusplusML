
#ifndef VISIBILITY_HPP_
# define VISIBILITY_HPP_

namespace AST
{
  enum class Visibility
  {
    PRIVATE,
      PROTECTED,
      PUBLIC,
      NotAvailable,
      };

  std::ostream &operator<<(std::ostream &o, Visibility v);
}

#endif	// !VISIBILITY_HPP_
