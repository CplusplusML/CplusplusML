#ifndef _COMPLEX_H_
# define _COMPLEX_H_

# include <set>
# include <list>
# include <string>
# include <iostream>

# include "basic.hh"
# include "members.hh"

namespace Object
{
  class Arrow_;

  class Complex_ : public Basic_
  {
  public:

    Complex_(): title_("Test") { Render(); }
    virtual     ~Complex_() { }

    void        Render(void);
    void        AddArrow(Arrow_ *arrow);
    void        RemoveArrow(Arrow_ *arrow);
    inline void	setAttrVisible(bool v) { isAttrVisible_ = v; }
    inline void	setOpeVisible(bool v) { isOpeVisible_ = v; }
    int         X() const { return x_; }
    int         Y() const { return y_; }

  private:
    virtual char        Label_() = 0;

  public:
    std::string         title_;
    bool		isAbstract_;
    std::list<Members::Attribute *> attributes_;
    std::list<Members::Operation *> operations_;

    std::set<Arrow_*>   arrows_;

    // QT
  protected:
    QLabel		titleLabel_;
    QGraphicsRectItem	titleRect_;
    QGraphicsRectItem	attrRect_;
    QGraphicsRectItem	opeRect_;

  protected:
    int x_;
    int y_;
    bool		isAttrVisible_;
    bool		isOpeVisible_;
  };
}

#endif /* _COMPLEX_H_ */
