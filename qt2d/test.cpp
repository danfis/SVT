#include <QApplication>

#include "main_window.hpp"
#include "painter.hpp"
#include "obj.hpp"

svt_obj_t *svtobj();
svt_obj_t *svtobj2();

int main(int argc, char *argv[])
{
    svt_obj_t *o;
    SVT::Qt2D::Obj *obj;

    QApplication app(argc, argv);

    SVT::Qt2D::MainWindow mw;

    o = svtobj();
    obj = new SVT::Qt2D::Obj(o);
    mw.addObj(obj);
    svtObjDelete(o);

    o = svtobj2();
    obj = new SVT::Qt2D::Obj(o);
    mw.addObj(obj);
    svtObjDelete(o);

    mw.show();

    return app.exec();
}


svt_obj_t *svtobj()
{
    svt_obj_t *obj = svtObjNew();

    svtObjAddPoint(obj, 0., -100., 0.);
    svtObjAddPoint(obj, 100., 0., 0.);
    svtObjAddPoint(obj, 0., 0., 0.);

    svtObjAddEdge(obj, 0, 1);
    svtObjAddEdge(obj, 1, 2);

    svtObjAddFace(obj, 0, 1, 2);

    svtObjSetName(obj, "TEST OBJ");

    return obj;
}

svt_obj_t *svtobj2()
{
    svt_obj_t *obj = svtObjNew();

    svtObjAddPoint(obj, 200., -200., 0.);
    svtObjAddPoint(obj, 300., -150., 0.);
    svtObjAddPoint(obj, 250., -200., 0.);

    svtObjAddEdge(obj, 0, 1);
    svtObjAddEdge(obj, 1, 2);

    svtObjAddFace(obj, 0, 1, 2);

    svtObjSetName(obj, "TEST OBJ 2");

    return obj;
}
