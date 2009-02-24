/**
 * SVT
 * ----------
 * Copyright (c)2007,2008,2009 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of SVT
 *
 * SVT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SVT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SVT. If not, see <http://www.gnu.org/licenses/>.
 */

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

