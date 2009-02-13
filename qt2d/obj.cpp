#include "obj.hpp"

SVT::Qt2D::Obj::Obj(svt_obj_t *obj)
    : _points(0), _edges(0), _faces(0)
{
    const char *name;

    name = svtObjName(obj);
    if (name != NULL)
        _name = name;

    if (svtObjNumPoints(obj) > 0)
        _points = new Points(obj);

    if (svtObjNumEdges(obj) > 0)
        _edges = new Edges(obj);

    if (svtObjNumFaces(obj) > 0)
        _faces = new Faces(obj);
}

SVT::Qt2D::Obj::~Obj()
{
    if (_points != 0)
        delete _points;
    if (_edges != 0)
        delete _edges;
    if (_faces != 0)
        delete _faces;
}

void SVT::Qt2D::Obj::pointColor(float *r, float *g, float *b) const
{
    qreal rr, rg, rb;

    if (_points){
        _points->color().getRgbF(&rr, &rg, &rb);
        *r = rr;
        *g = rg;
        *b = rb;
    }
}

void SVT::Qt2D::Obj::edgeColor(float *r, float *g, float *b) const
{
    qreal rr, rg, rb;

    if (_edges){
        _edges->color().getRgbF(&rr, &rg, &rb);
        *r = rr;
        *g = rg;
        *b = rb;
    }
}

void SVT::Qt2D::Obj::faceColor(float *r, float *g, float *b) const
{
    qreal rr, rg, rb;

    if (_faces){
        _faces->color().getRgbF(&rr, &rg, &rb);
        *r = rr;
        *g = rg;
        *b = rb;
    }
}
