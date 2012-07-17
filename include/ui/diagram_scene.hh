#ifndef		_CPLUSPLUSML_UI_DIAGRAM_SCENE_HH_
# define	_CPLUSPLUSML_UI_DIAGRAM_SCENE_HH_

#include	<QGraphicsScene>

#include	"object/basic.hh"

namespace			CplusplusML
{
  class				DiagramScene: public QGraphicsScene
  {
    Q_OBJECT

  public:
    enum			Mode
      {
	modeInsertItem,
	modeMoveItem
      };

    inline void			setCurrentItem(Object::ObjectType item)
    {
      currentItem_ = item;
    }

    inline Object::ObjectType	getCurrentItem(void) const
    {
      return (currentItem_);
    }

    inline void			setMode(Mode mode)
    {
      currentMode_ = mode;
    }

    inline Mode			getMode(void) const
    {
      return (currentMode_);
    }

  private:

    Object::ObjectType		currentItem_;
    Mode			currentMode_;
  };
}

#endif		// _CPLUSPLUSML_UI_DIAGRAM_SCENE_HH_
