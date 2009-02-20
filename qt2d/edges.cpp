#include "edges.hpp"



SVT::Qt2D::Edges::Edges(svt_obj_t *obj)
    : _num_edges(0)
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
        _path.moveTo(points[id1][0], -1. * points[id1][1]);
        _path.lineTo(points[id2][0], -1. * points[id2][1]);

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
}

void SVT::Qt2D::Edges::paint(QPainter &painter, const QRectF &rect)
{
    QPen cpen = pen(); // current pen
    qreal fx, tx, omit; // for recomputing of width
    qreal size;

    if (!on())
        return;

    // compute correct line width
    painter.worldMatrix().map(0., 0., &fx, &omit);
    painter.worldMatrix().map(1, 0., &tx, &omit);
    size = _size * (1 / (tx - fx));
    cpen.setWidthF(size);

    painter.setPen(cpen);
    painter.drawPath(_path);
}
