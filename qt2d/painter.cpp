#include "painter.hpp"


namespace SVT {

namespace Qt2D {


Painter::Painter(QWidget *parent)
    : QWidget(parent), _paths(0), _paths_len(0)
{
    QPainterPath *path;

    _paths = new QPainterPath*[1];

    _paths[_paths_len++] = path = new QPainterPath();

    path->moveTo(10, 10);
    path->lineTo(20, 20);
}

Painter::~Painter()
{
    for (int i=0; i < _paths_len; i++){
        if (_paths[i] != 0)
            delete _paths[i];
    }

    delete [] _paths;
}


void Painter::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    for (int i=0; i < _paths_len; i++){
        if (_paths[i] != 0)
            painter.drawPath(*_paths[i]);
    }

    painter.end();
}


} /* Qt2D */

} /* SVT */
