#include "points.hpp"


SVT::Qt2D::Points::Points(svt_obj_t *obj)
{
    const svt_point_t *points;
    const float *color;

    // copy all points from obj to _points
    points = svtObjPoints(obj, &_points_len);
    _points = new QPointF*[_points_len]; // allocate memory

    for (int i=0; i < _points_len; i++){
        // ignore third coordinate
        _points[i] = new QPointF(points[i][0], -1. * points[i][1]);

        _setPointInBoundingRect(points[i]);
    }

    // get color
    color = svtObjPointColor(obj);
    if (color != NULL)
        setColor(color[0], color[1], color[2]);

    // set size
    setSize(1.);
}

SVT::Qt2D::Points::~Points()
{
    for (int i=0; i < _points_len; i++)
        delete _points[i];
    delete [] _points;
}


void SVT::Qt2D::Points::paint(QPainter &painter)
{
    QRectF p(0., 0., _size, _size);

    if (!on())
        return;

    painter.setPen(pen());

    for (int i=0; i < _points_len; i++){
        p.moveCenter(*_points[i]);
        painter.fillRect(p, pen().brush());
    }
}

