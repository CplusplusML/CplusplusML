#include <cmath>

#include <QPointF>
#include <QTransform>
#include <QPainter>

#include "object/basic.hh"
#include "ui/qt/link_head_graphics_item.hh"

namespace CplusplusML
{
  namespace Ui
  {
    namespace Qt
    {
      std::unordered_map<int, LinkHead::HeadData> LinkHead::initHeadTemplates()
      {
        std::unordered_map<int, LinkHead::HeadData>   map;
        QPainterPath simpleHeadPath(QPointF(0, 0));

        {
          qreal slope = 2.5 * M_PI / 3;
          static const int magic = 6;

          simpleHeadPath.lineTo(QPointF(std::sin(slope) * magic, std::cos(slope) * magic));
          simpleHeadPath.lineTo(QPointF(std::sin(-slope) * magic, std::cos(-slope) * magic));
          simpleHeadPath.closeSubpath();
        }

        // SIMPLE
        {
          map.insert(std::pair<int, LinkHead::HeadData>((int)LinkHead::Type::SIMPLE_FILLED,
            {simpleHeadPath, ::Qt::black}));
        }
        return map;
      }

      std::unordered_map<int, LinkHead::HeadData> LinkHead::headTemplates = initHeadTemplates();

      LinkHead::LinkHead() :
        _type(Type::NONE)
      {
      }

      LinkHead::~LinkHead()
      {
      }

      QRectF LinkHead::boundingRect() const
      {
        HeadData headData = this->getHeadData();

        return (headData.path.boundingRect());
      }

      void LinkHead::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
      {
        HeadData headData = this->getHeadData();

        painter->setBrush(headData.brush);
        painter->drawPath(headData.path);
      }

      void    LinkHead::setAngle(qreal const& angle)
      {
        this->_angle = angle;
      }

      void    LinkHead::setOrigin(QPointF const& origin)
      {
        this->_origin = origin;
      }

      void    LinkHead::setSize(qreal const& size)
      {
        this->_size = size;
      }

      void    LinkHead::setType(LinkHead::Type const& type)
      {
        this->_type = type;
      }

      LinkHead::HeadData LinkHead::getHeadData() const
      {
        auto it = headTemplates.find((int)this->_type);

        if (it != headTemplates.end())
          {
            QTransform transform;

            transform.translate(this->_origin.x(), this->_origin.y());
            transform.scale(this->_size, this->_size);
            transform.rotateRadians(this->_angle);
            return HeadData {transform.map(it->second.path), it->second.brush};
          }
        return HeadData();
      }
    }
  }
}
