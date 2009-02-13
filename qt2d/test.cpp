#include <QApplication>

#include "../qt/main_window.hpp"
#include "painter.hpp"
#include "obj.hpp"

svt_obj_t *svtobj();

int main(int argc, char *argv[])
{
    SVT::Qt2D::Obj *obj = new SVT::Qt2D::Obj(svtobj());

    QApplication app(argc, argv);

    SVT::Qt::MainWindow mw;
    mw.addObjWidget(obj);

    mw.setCentralWidget(new SVT::Qt2D::Painter());

    mw.show();

    return app.exec();
}


svt_obj_t *svtobj()
{
    svt_obj_t *obj = svtObjNew();

    svtObjAddPoint(obj, 0., 0., 0.);
    svtObjAddPoint(obj, 1., 1., 0.);
    svtObjAddPoint(obj, 0., 1., 0.);

    svtObjAddEdge(obj, 0, 1);
    svtObjAddEdge(obj, 1, 2);

    svtObjAddFace(obj, 0, 1, 2);

    svtObjSetName(obj, "TEST OBJ");

    return obj;
}
