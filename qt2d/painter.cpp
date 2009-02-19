#include "painter.hpp"
using namespace std;


#include "painter.moc"


namespace SVT {

namespace Qt2D {


Painter::Painter(QWidget *parent)
    : QWidget(parent)
{
}

Painter::~Painter()
{
}


void Painter::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    list<Obj *>::iterator it, it_end;

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
