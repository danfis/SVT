#ifndef SVT_QT2D_PAINTER_HPP
#define SVT_QT2D_PAINTER_HPP

#include <QWidget>
#include <QPainter>
#include <QLinkedList>
#include <QRectF>
#include <QMatrix>
#include <list>

#include "obj.hpp"

namespace SVT {

namespace Qt2D {

class Painter : public QWidget {
    Q_OBJECT

  private:
    std::list<Obj *> _objs;
    QMatrix _tr; /*! transformation */
    QRectF _brect;
    bool _brect_init;

  protected:
    void paintEvent(QPaintEvent *e);

  public:
    Painter(QWidget *parent = 0);
    ~Painter();

    void addObj(Obj *o);
    void scaleToWindow();

  public slots:
    void repaint(Common::Obj *o = 0);
};

} /* Qt2D */

} /* SVT */

#endif
