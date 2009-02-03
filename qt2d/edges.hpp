#ifndef SVT_QT2D_EDGES_HPP
#define SVT_QT2D_EDGES_HPP

#include "../parser/obj.h"
#include "elements.hpp"

namespace SVT {

namespace Qt2D {

class Edges : public Elements {
  private:
    QPainterPath _path;

  public:
    Edges(svt_obj_t *obj);
    ~Edges();

    void paint(QPainter &painter);
};

} /* Qt2D */

} /* SVT */

#endif

