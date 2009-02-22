#include "obj.hpp"
#include "painter.hpp"

SVT::Qt2D::Obj::Obj(svt_obj_t *obj)
    : _points(0), _edges(0), _faces(0), _all_on(true), _painter(0)
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


    // set up bounding rectangle
    if (_points != 0)
        _brect = _points->boundingRect();
    else if (_edges != 0)
        _brect = _edges->boundingRect();
    else if (_faces != 0)
        _brect = _faces->boundingRect();

    if (_points != 0 && _edges != 0){
        const QRectF &br = _edges->boundingRect();

        if (br.left() < _brect.left())
            _brect.setLeft(br.left());
        if (br.right() > _brect.right())
            _brect.setRight(br.right());
        if (br.top() < _brect.top())
            _brect.setTop(br.top());
        if (br.bottom() > _brect.bottom())
            _brect.setBottom(br.bottom());
    }

    if ((_points != 0 || _edges != 0) && _faces != 0){
        const QRectF &br = _faces->boundingRect();

        if (br.left() < _brect.left())
            _brect.setLeft(br.left());
        if (br.right() > _brect.right())
            _brect.setRight(br.right());
        if (br.top() < _brect.top())
            _brect.setTop(br.top());
        if (br.bottom() > _brect.bottom())
            _brect.setBottom(br.bottom());
    }
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

void SVT::Qt2D::Obj::update()
{
    if (_painter != 0)
        _painter->update(this);
}
