#include <iostream>
#include "painter.hpp"
using namespace std;


#include "painter.moc"


namespace SVT {

namespace Qt2D {


Painter::Painter(QWidget *parent)
    : QWidget(parent), _brect_init(false)
{
}

Painter::~Painter()
{
}

void Painter::addObj(Obj *o)
{
    _objs.push_back(o);

    if (!_brect_init){
        const QRectF &br = o->boundingRect();

        _brect = br;
        _brect_init = true;
    }else{
        const QRectF &br = o->boundingRect();

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

void Painter::scaleToWindow()
{
    QSize wsize = size();
    qreal scale, dx, dy, tmp;
    QPointF center = _brect.center();
    QPointF wcenter(wsize.width() / 2., wsize.height() / 2.);

    // scale:
    tmp = (qreal)wsize.width() / _brect.width();
    scale = (qreal)wsize.height() / _brect.height();
    if (tmp < scale)
        scale = tmp;

    // dx, dy
    center *= scale;
    dx = wcenter.x() - center.x();
    dy = wcenter.y() - center.y();
    
    // set up transform matrix
    _tr.reset();
    _tr.translate(dx, dy);
    _tr.scale(scale, scale);
}


void Painter::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    list<Obj *>::iterator it, it_end;

    painter.setWorldMatrix(_tr);

    it = _objs.begin();
    it_end = _objs.end();
    for (; it != it_end; ++it){
        (*it)->paint(painter);
    }

    painter.end();
}


void Painter::repaint(Common::Obj *_o)
{
    //Obj *o = (Obj *)_o;

    update();
}


} /* Qt2D */

} /* SVT */
