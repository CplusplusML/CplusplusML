#ifndef         _CPLUSPLUSML_UI_QT_LINK_HEAD_GRAPHICS_ITEM_HH_
# define        _CPLUSPLUSML_UI_QT_LINK_HEAD_GRAPHICS_ITEM_HH_

# include <unordered_map>

# include <QtGlobal>
# include <QGraphicsObject>

namespace CplusplusML
{
  namespace Ui
  {
    namespace Qt
    {
      class LinkHead : public QGraphicsObject
      {
      public:
        enum class Type
        {
          NONE,
          SIMPLE_FILLED,
          SIMPLE_EMPTY,
          DOUBLE_FILLED,
          DIAMOND_FILLED,
          DIAMOND_EMPTY
        };

        LinkHead();
        virtual ~LinkHead();

        virtual QRectF boundingRect() const;
        virtual void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

        void    setAngle(qreal const& angle);
        void    setOrigin(QPointF const& origin);
        void    setSize(qreal const& size);
        void    setType(LinkHead::Type const& type);

      private:
        struct HeadData
        {
          QPainterPath     path;
          QBrush           brush;
        };

        static std::unordered_map<int, LinkHead::HeadData> initHeadTemplates();
        static std::unordered_map<int, LinkHead::HeadData>   headTemplates;

        HeadData const& headData();

        QPointF _origin;
        qreal _angle;
        qreal _size;
        LinkHead::Type _type;

      protected:
        HeadData getHeadData() const;
      };
    }
  }
}

#endif  // !_CPLUSPLUSML_UI_QT_LINK_HEAD_GRAPHICS_ITEM_HH_
