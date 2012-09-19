#ifndef _COMPLEX_H_
# define _COMPLEX_H_

# include <QLabel>
# include <QGraphicsRectItem>
# include <QGraphicsProxyWidget>
# include <QGraphicsSimpleTextItem>

# include <set>
# include <list>
# include <string>

# include "ui/complex_property_window.hh"

# include "basic.hh"
# include "members.hh"
# include "arrow_connection.hh"

namespace			Object
{
  class				Arrow_;
  class ArrowConnection;

  class				Complex_ : public Basic_
  {
  public:

    Complex_(): title_("Test") { Render(); }
    virtual ~Complex_();


    void			AddArrow(Arrow_ *arrow);
    void			RemoveArrow(Arrow_ *arrow);

    inline bool			getAttrVisible(void) const { return isAttrVisible_; }
    inline bool			getOpeVisible(void) const { return isOpeVisible_; }
    inline void			setAttrVisible(bool v) { isAttrVisible_ = v; }
    inline void			setOpeVisible(bool v) { isOpeVisible_ = v; }


    inline int			X() const { return x_; }
    inline int			Y() const { return y_; }

    void			updateFromForm(CplusplusML::ComplexPropertyWindow const &properties);

  private:
    void			Render(void);
    virtual char		Label_() = 0;

    void adjustConnections();

  public:
    std::string			title_;
    bool			isAbstract_;
    std::list<Members::Attribute *> attributes_;
    std::list<Members::Operation *> operations_;

    // QT
  protected:

    QGraphicsSimpleTextItem	*titleLabel_;
    QGraphicsRectItem		*titleRect_;
    QGraphicsRectItem		*attrRect_;
    QGraphicsRectItem		*opeRect_;

  protected:
    int				x_;
    int				y_;
    bool			isAttrVisible_;
    bool			isOpeVisible_;
    QVector<ArrowConnection*> connections;
  };
}

#endif /* _COMPLEX_H_ */
