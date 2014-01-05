#ifndef _CPLUSPLUSML_UI_DIAGRAM_ITEM_H_
# define _CPLUSPLUSML_UI_DIAGRAM_ITEM_H_

# include <QGraphicsItemGroup>

namespace       cplusplusml {
  namespace     ui {

    /*
      An item is the graphic representation of cppml object in the
      diagram scene.
    */
    class       DiagramItem: public QGraphicsItemGroup
    {
    public:
      enum Type {
        item_cursor,
        item_class,
        item_struct,
        item_enum,
        item_union,
        item_namespace,
        item_typedef,
        item_aggregation,
        item_dependency,
        item_composition,
        item_inheritance,
        item_free_function,
        item_template,
        item_library
      };

      DiagramItem(QGraphicsItem* parent);
      ~DiagramItem();

    };
  }
}

#endif // _CPLUSPLUSML_UI_DIAGRAM_ITEM_H_
