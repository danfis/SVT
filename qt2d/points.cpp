#include <iostream>
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


void SVT::Qt2D::Points::paint(QPainter &painter, const QRectF &rect)
{
    QRectF p; // rectangle which will be drawed as point
    qreal fx, tx, omit; // for recomputing size of points using world transf.
    qreal size;

    if (!on())
        return;

    // first compute dimensions of rectangle
    painter.worldMatrix().map(0., 0., &fx, &omit);
    painter.worldMatrix().map(1, 0., &tx, &omit);
    size = _size * (1 / (tx - fx));
    p.setHeight(size);
    p.setWidth(size);


    painter.setPen(pen());

    for (int i=0; i < _points_len; i++){
        p.moveCenter(*_points[i]);

        if (rect.intersects(p)){
            painter.fillRect(p, pen().brush());
        }
    }
}

