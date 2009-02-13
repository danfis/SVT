#include "edges.hpp"



SVT::Qt2D::Edges::Edges(svt_obj_t *obj)
{
    const svt_edge_t *edges;
    int edges_len;
    const svt_point_t *points;
    int points_len;
    int id1, id2;
    const float *color;

    // save edges to path
    points = svtObjPoints(obj, &points_len);
    edges = svtObjEdges(obj, &edges_len);
    for (int i=0; i < edges_len; i++){
        id1 = edges[i][0];
        id2 = edges[i][1];
        _path.moveTo(points[id1][0], points[id1][1]);
        _path.lineTo(points[id2][0], points[id2][1]);
    }

    // get color
    color = svtObjEdgeColor(obj);
    if (color != NULL)
        setColor(color[0], color[1], color[2]);

    // get size
    setSize(1.);
}

SVT::Qt2D::Edges::~Edges()
{
}

void SVT::Qt2D::Edges::paint(QPainter &painter)
{
    if (!on())
        return;

    painter.setPen(pen());
    painter.drawPath(_path);
}
