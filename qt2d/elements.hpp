#ifndef SVT_QT2D_ELEMENTS_HPP
#define SVT_QT2D_ELEMENTS_HPP

#include <QColor>
#include <QPen>
#include <QPainter>

namespace SVT {

namespace Qt2D {

/**
 * Base class for points, edges and faces.
 */
class Elements {
  protected:
    QPen _pen;
    QColor _color;
    qreal _size;

  public:
    void setColor(float r, float g, float b)
        { _color.setRgbF(r, g, b);
          _pen.setColor(_color);}

    void setSize(float s)
        { if (s > 0.) _size = s;
          _pen.setWidthF(_size); }

    const QColor &color() const { return _color; }
    qreal size() const { return _size; }
    const QPen &pen() const { return _pen; }

    void paint(QPainter &painter){};
};

} /* Qt2D */

} /* SVT */

#endif

