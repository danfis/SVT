#ifndef SVT_QT2D_PAINTER_HPP
#define SVT_QT2D_PAINTER_HPP

#include <QWidget>
#include <QPainter>
#include <QLinkedList>
#include <QRectF>
#include <QMatrix>
#include <QWheelEvent>
#include <list>

#include "obj.hpp"

namespace SVT {

namespace Qt2D {

class Painter : public QWidget {
    Q_OBJECT

  private:
    std::list<Obj *> _objs;
    qreal _scale, _dx, _dy; /*! world transfomataions */
    bool _mouse_pressed; /*! indicates if mouse's left button is pressed */
    QPoint _mouse_pos; /*! last position of mouse */


  protected:
    void paintEvent(QPaintEvent *e);

  public:
    Painter(QWidget *parent = 0);
    ~Painter();

    void addObj(Obj *o);

    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

  public slots:
    void repaint(Common::Obj *o = 0);
    void setScale(double val);
    void setTranslation(double dx, double dy);
    void fitToWin();

  signals:
    void scaleChanged(double val);
};

} /* Qt2D */

} /* SVT */

#endif
