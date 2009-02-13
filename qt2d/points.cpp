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
        _points[i] = new QPointF(points[i][0], points[i][1]);
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
    if (!on())
        return;

    painter.setPen(pen());

    for (int i=0; i < _points_len; i++){
        painter.drawPoint(*_points[i]);
    }
}

