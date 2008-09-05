#include <QApplication>
#include <QMainWindow>
#include <iostream>
using namespace std;

#include "obj_widget.hpp"
#include "obj_style_widget.hpp"
#include "main_window.hpp"
#include "../common/obj.hpp"

class MainWindow;


class Obj : public SVT::Common::Obj {
  private:
    std::string _name;
    SVT::Qt::MainWindow *_win;
    int _faces;

    static int faces;

  public:
    Obj(std::string &name, SVT::Qt::MainWindow *win)
        : _name(name), _win(win){ _faces = faces++; }
    Obj(const char *name, SVT::Qt::MainWindow *win)
        : _name(name), _win(win){ _faces = faces++; }
    const std::string &name() const { return _name; }

    int numPoints() const { return 10; }
    int numEdges() const { return 12; }
    int numFaces() const { return _faces; }

    bool pointsOn() const { return true; }
    bool edgesOn() const { return false; }
    bool facesOn() const { return true; }
    bool allOn() const { return true; }

    float pointSize() const { return 1.f; }
    float edgeWidth() const { return 2.f; }

    void pointColor(float *r, float *g, float *b) const
        { *r = 1.; *g = 0.5; *b = 0.1; }
    float pointColorRed() const { return 1.; }
    float pointColorGreen() const { return 0.5; }
    float pointColorBlue() const { return 0.1; }

    void edgeColor(float *r, float *g, float *b) const
        { *r = 0.5; *g = 0.1; *b = 1.; }
    float edgeColorRed() const { return 0.5; }
    float edgeColorGreen() const { return 0.1; }
    float edgeColorBlue() const { return 1.; }

    void faceColor(float *r, float *g, float *b) const
        { *r = 0.1; *g = 1.; *b = 0.5; }
    float faceColorRed() const { return 0.1; }
    float faceColorGreen() const { return 1.; }
    float faceColorBlue() const { return 0.5; }

    void setAllOn(bool on = true)
    {
        QString msg = QString("%1: setAllOn(%2)")
                        .arg(_name.c_str())
                        .arg(on);
        _win->showMsgInStatusBar(msg);
    }

    void setPointsOn(bool on = true)
    {
        QString msg = QString("%1: setPointsOn(%2)")
                        .arg(_name.c_str())
                        .arg(on);
        _win->showMsgInStatusBar(msg);
    }
    void setEdgesOn(bool on = true)
    {
        QString msg = QString("%1: setEdgesOn(%2)")
                        .arg(_name.c_str())
                        .arg(on);
        _win->showMsgInStatusBar(msg);
    }
    void setFacesOn(bool on = true)
    {
        QString msg = QString("%1: setFacesOn(%2)")
                        .arg(_name.c_str())
                        .arg(on);
        _win->showMsgInStatusBar(msg);
    }

    void setPointSize(float size)
    {
        QString msg = QString("%1: setPointSize(%2)")
                        .arg(_name.c_str())
                        .arg(size);
        _win->showMsgInStatusBar(msg);
    }

    void setEdgeWidth(float width)
    {
        QString msg = QString("%1: setEdgeWidth(%2)")
                        .arg(_name.c_str())
                        .arg(width);
        _win->showMsgInStatusBar(msg);
    }

    void setPointColor(float r, float g, float b)
    {
        QString msg = QString("%1: setPointColor(%2, %3, %4)")
                        .arg(_name.c_str())
                        .arg(r)
                        .arg(g)
                        .arg(b);
        _win->showMsgInStatusBar(msg);
    }
    void setPointColorRed(float v)
    {
        QString msg = QString("%1: setPointColorRed(%2)")
                        .arg(_name.c_str())
                        .arg(v);
        _win->showMsgInStatusBar(msg);
    }
    void setPointColorGreen(float v)
    {
        QString msg = QString("%1: setPointColorGreen(%2)")
                        .arg(_name.c_str())
                        .arg(v);
        _win->showMsgInStatusBar(msg);
    }
    void setPointColorBlue(float v)
    {
        QString msg = QString("%1: setPointColorBlue(%2)")
                        .arg(_name.c_str())
                        .arg(v);
        _win->showMsgInStatusBar(msg);
    }

    void setEdgeColor(float r, float g, float b)
    {
        QString msg = QString("%1: setEdgeColor(%2, %3, %4)")
                        .arg(_name.c_str())
                        .arg(r)
                        .arg(g)
                        .arg(b);
        _win->showMsgInStatusBar(msg);
    }
    void setEdgeColorRed(float v)
    {
        QString msg = QString("%1: setEdgeColorRed(%2)")
                        .arg(_name.c_str())
                        .arg(v);
        _win->showMsgInStatusBar(msg);
    }
    void setEdgeColorGreen(float v)
    {
        QString msg = QString("%1: setEdgeColorGreen(%2)")
                        .arg(_name.c_str())
                        .arg(v);
        _win->showMsgInStatusBar(msg);
    }
    void setEdgeColorBlue(float v)
    {
        QString msg = QString("%1: setEdgeColorBlue(%2)")
                        .arg(_name.c_str())
                        .arg(v);
        _win->showMsgInStatusBar(msg);
    }

    void setFaceColor(float r, float g, float b)
    {
        QString msg = QString("%1: setFaceColor(%2, %3, %4)")
                        .arg(_name.c_str())
                        .arg(r)
                        .arg(g)
                        .arg(b);
        _win->showMsgInStatusBar(msg);
    }
    void setFaceColorRed(float v)
    {
        QString msg = QString("%1: setFaceColorRed(%2)")
                        .arg(_name.c_str())
                        .arg(v);
        _win->showMsgInStatusBar(msg);
    }
    void setFaceColorGreen(float v)
    {
        QString msg = QString("%1: setFaceColorGreen(%2)")
                        .arg(_name.c_str())
                        .arg(v);
        _win->showMsgInStatusBar(msg);
    }
    void setFaceColorBlue(float v)
    {
        QString msg = QString("%1: setFaceColorBlue(%2)")
                        .arg(_name.c_str())
                        .arg(v);
        _win->showMsgInStatusBar(msg);
    }
};

class MainWindow : public SVT::Qt::MainWindow {
  public:
    MainWindow()
    {
        addObjWidget(new Obj("1", this));
        addObjWidget(new Obj("Some name", this));

        setCentralWidget(new QWidget());
    }
};

int Obj::faces = 0;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow win;

    win.show();
    app.exec();
}

