#ifndef _CPLUSPLUSML_UI_DIAGRAM_SCENE_H
# define _CPLUSPLUSML_UI_DIAGRAM_SCENE_H

# include <QGraphicsScene>

namespace       cplusplusml {
  namespace     ui {

    /*
      The scene containing all graphic elements and handling events.
    */
    class       DiagramScene: public QGraphicsScene
    {
    public:
      enum      Mode {
        Select,
        InsertItem,
        InsertArrow,
        MoveItem
      };

      DiagramScene(QObject* parent);
      ~DiagramScene();

    public slots:
      void      setMode(Mode mode);

    private:
      Mode      current_mode_;
    };
  }
}

#endif // _CPLUSPLUSML_UI_DIAGRAM_SCENE_H
