#ifndef SVT_QT2D_EDGES_HPP
#define SVT_QT2D_EDGES_HPP

#include "../parser/obj.h"
#include "elements.hpp"

namespace SVT {

namespace Qt2D {

class Edges : public Elements {
  private:
    QPainterPath _path;
    int _num_edges;

  public:
    Edges(svt_obj_t *obj);
    ~Edges();

    int numEdges() const { return _num_edges; }

    void paint(QPainter &painter, const QRectF &rect);
};

} /* Qt2D */

} /* SVT */

#endif

