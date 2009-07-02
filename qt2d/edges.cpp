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

#include "edges.hpp"
#include "common/msg.hpp"



SVT::Qt2D::Edges::Edges(svt_obj_t *obj)
    : _num_edges(0)
{
    const svt_edge_t *edges;
    int edges_len;
    const svt_point_t *points;
    int points_len;
    int id1, id2;
    const float *color;
    QLineF *line;

    // save edges to path
    points = svtObjPoints(obj, &points_len);
    edges = svtObjEdges(obj, &edges_len);
    for (int i=0; i < edges_len; i++){
        id1 = edges[i][0];
        id2 = edges[i][1];

        line = new QLineF(points[id1][0], -1. * points[id1][1],
                          points[id2][0], -1. * points[id2][1]);
        _lines.push_back(line);

        _setPointInBoundingRect(points[id1]);
        _setPointInBoundingRect(points[id2]);
    }
    _num_edges = edges_len;

    // get color
    color = svtObjEdgeColor(obj);
    if (color != NULL)
        setColor(color[0], color[1], color[2]);

    // get size
    setSize(1.);
}

SVT::Qt2D::Edges::~Edges()
{
    std::list<QLineF *>::iterator it, it_end;

    it = _lines.begin();
    it_end = _lines.end();
    for (; it != it_end; ++it){
        delete *it;
    }
}

void SVT::Qt2D::Edges::paint(QPainter &painter, const QRectF &rect)
{
    QPen cpen = pen(); // current pen
    qreal fx, tx, omit; // for recomputing of width
    qreal size;
    std::list<QLineF *>::iterator it, it_end;

    if (!on())
        return;

    // compute correct line width
    painter.worldMatrix().map(0., 0., &fx, &omit);
    painter.worldMatrix().map(1, 0., &tx, &omit);
    size = _size * (1 / (tx - fx));
    cpen.setWidthF(size);

    painter.setPen(cpen);

    it = _lines.begin();
    it_end = _lines.end();
    for (; it != it_end; ++it){
        if (rect.contains((*it)->p1()) || rect.contains((*it)->p2())){
            painter.drawLine(**it);
        }
    }
}
