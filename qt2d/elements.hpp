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
    bool _on;

  public:
    Elements() : _on(true){}

    void setColor(float r, float g, float b)
        { _color.setRgbF(r, g, b); _pen.setColor(_color);}
    void setColorRed(float v)
        { _color.setRedF(v); _pen.setColor(_color);}
    void setColorGreen(float v)
        { _color.setGreenF(v); _pen.setColor(_color);}
    void setColorBlue(float v)
        { _color.setBlueF(v); _pen.setColor(_color);}

    void setSize(float s)
        { if (s > 0.) _size = s;
          _pen.setWidthF(_size); }

    void setOn(bool on) { _on = on; }

    const QColor &color() const { return _color; }
    qreal size() const { return _size; }
    const QPen &pen() const { return _pen; }
    bool on() const { return _on; }

    void paint(QPainter &painter){};
};

} /* Qt2D */

} /* SVT */

#endif

