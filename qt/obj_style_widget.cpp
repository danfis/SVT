#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "obj_style_widget.hpp"

#include "obj_style_widget.moc"

namespace Qt {

ObjStyleWidget::ObjStyleWidget(void *obj, ObjStyleWidgetFlags flags)
    : _obj(obj), _flags(flags)
{
    QVBoxLayout *layout = new QVBoxLayout;

    if ((OBJ_STYLE_WIDGET_POINTS & flags) != 0){
        layout->addWidget(_buildPoints());
    }
    if ((OBJ_STYLE_WIDGET_EDGES & flags) != 0){
        layout->addWidget(_buildEdges());
    }
    if ((OBJ_STYLE_WIDGET_FACES & flags) != 0){
        layout->addWidget(_buildFaces());
    }

    setLayout(layout);

    _setUpConnections();
}

void ObjStyleWidget::_setUpConnections()
{
    if ((OBJ_STYLE_WIDGET_POINTS & _flags) != 0){
        connect(_points[0], SIGNAL(valueChanged(double)),
                this, SLOT(_pointSize(float)));
        connect(_points[1], SIGNAL(valueChanged(double)),
                this, SLOT(_pointColorRed(float)));
        connect(_points[2], SIGNAL(valueChanged(double)),
                this, SLOT(_pointColorGreen(float)));
        connect(_points[3], SIGNAL(valueChanged(double)),
                this, SLOT(_pointColorBlue(float)));
        connect(_points_b, SIGNAL(toggle(bool)),
                this, SLOT(_pointOnOff(bool)));
    }


    if ((OBJ_STYLE_WIDGET_EDGES & _flags) != 0){
        connect(_edges[0], SIGNAL(valueChanged(double)),
                this, SLOT(_edgeSize(float)));
        connect(_edges[1], SIGNAL(valueChanged(double)),
                this, SLOT(_edgeColorRed(float)));
        connect(_edges[2], SIGNAL(valueChanged(double)),
                this, SLOT(_edgeColorGreen(float)));
        connect(_edges[3], SIGNAL(valueChanged(double)),
                this, SLOT(_edgeColorBlue(float)));
        connect(_edges_b, SIGNAL(toggle(bool)),
                this, SLOT(_edgeOnOff(bool)));
    }

    if ((OBJ_STYLE_WIDGET_FACES & _flags) != 0){
        connect(_faces[0], SIGNAL(valueChanged(double)),
                this, SLOT(_faceColorRed(float)));
        connect(_faces[1], SIGNAL(valueChanged(double)),
                this, SLOT(_faceColorGreen(float)));
        connect(_faces[2], SIGNAL(valueChanged(double)),
                this, SLOT(_faceColorBlue(float)));
        connect(_faces_b, SIGNAL(toggle(bool)),
                this, SLOT(_faceOnOff(bool)));
    }
}

void ObjStyleWidget::_buildColors(QVBoxLayout *layout, QDoubleSpinBox **refs)
{
    QHBoxLayout *hlayout = new QHBoxLayout;
    QDoubleSpinBox *spin;

    layout->addWidget(new QLabel("Color"));

    spin = new QDoubleSpinBox;
    spin->setRange(0, 1);
    spin->setSingleStep(0.05);
    refs[0] = spin;
    hlayout->addWidget(spin);

    spin = new QDoubleSpinBox;
    spin->setRange(0, 1);
    spin->setSingleStep(0.05);
    refs[2] = spin;
    hlayout->addWidget(spin);

    spin = new QDoubleSpinBox;
    spin->setRange(0, 1);
    spin->setSingleStep(0.05);
    refs[3] = spin;
    hlayout->addWidget(spin);

    layout->addLayout(hlayout);
}

void ObjStyleWidget::_buildSize(QVBoxLayout *layout, QDoubleSpinBox **refs)
{
    QDoubleSpinBox *spin;

    layout->addWidget(new QLabel("Size"));

    spin = new QDoubleSpinBox;
    spin->setRange(1, 10);
    spin->setSingleStep(0.1);
    refs[0] = spin;
    layout->addWidget(spin);
}

void ObjStyleWidget::_buildOnOff(QVBoxLayout *layout, QPushButton **refs)
{
    QPushButton *button;

    button = new QPushButton("On/Off");
    button->setCheckable(true);
    *refs = button;
    layout->addWidget(button);
}

QWidget *ObjStyleWidget::_buildPoints()
{
    QGroupBox *group = new QGroupBox("Points");
    QVBoxLayout *layout = new QVBoxLayout;

    // Size
    _buildSize(layout, _points);

    // Color
    _buildColors(layout, _points + 1);

    // OnOff
    _buildOnOff(layout, &_points_b);

    group->setLayout(layout);
    return group;
}

QWidget *ObjStyleWidget::_buildEdges()
{
    QGroupBox *group = new QGroupBox("Edges");
    QVBoxLayout *layout = new QVBoxLayout;

    // Size
    _buildSize(layout, _edges);

    // Color
    _buildColors(layout, _edges + 1);

    // OnOff
    _buildOnOff(layout, &_edges_b);

    group->setLayout(layout);
    return group;
}

QWidget *ObjStyleWidget::_buildFaces()
{
    QGroupBox *group = new QGroupBox("Faces");
    QVBoxLayout *layout = new QVBoxLayout;

    // Color
    _buildColors(layout, _faces);

    // OnOff
    _buildOnOff(layout, &_faces_b);

    group->setLayout(layout);
    return group;
}


// PRIVATE SLOTS:
void ObjStyleWidget::_pointSize(float val)
    { emit pointSize(_obj, val); }
void ObjStyleWidget::_pointColorRed(float val)
    { emit pointColorRed(_obj, val); }
void ObjStyleWidget::_pointColorBlue(float val)
    { emit pointColorBlue(_obj, val); }
void ObjStyleWidget::_pointColorGreen(float val)
    { emit pointColorGreen(_obj, val); }
void ObjStyleWidget::_pointColor(float r, float g, float b)
    { emit pointColor(_obj, r, g, b); }
void ObjStyleWidget::_pointOnOff(bool on)
    { emit pointOnOff(_obj, on); }

void ObjStyleWidget::_edgeWidth(float val)
    { emit edgeWidth(_obj, val); }
void ObjStyleWidget::_edgeColorRed(float val)
    { emit edgeColorRed(_obj, val); }
void ObjStyleWidget::_edgeColorBlue(float val)
    { emit edgeColorBlue(_obj, val); }
void ObjStyleWidget::_edgeColorGreen(float val)
    { emit edgeColorGreen(_obj, val); }
void ObjStyleWidget::_edgeColor(float r, float g, float b)
    { emit edgeColor(_obj, r, g, b); }
void ObjStyleWidget::_edgeOnOff(bool on)
    { emit edgeOnOff(_obj, on); }

void ObjStyleWidget::_faceColorRed(float val)
    { emit faceColorRed(_obj, val); }
void ObjStyleWidget::_faceColorBlue(float val)
    { emit faceColorBlue(_obj, val); }
void ObjStyleWidget::_faceColorGreen(float val)
    { emit faceColorGreen(_obj, val); }
void ObjStyleWidget::_faceColor(float r, float g, float b)
    { emit faceColor(_obj, r, g, b); }
void ObjStyleWidget::_faceOnOff(bool on)
    { emit faceOnOff(_obj, on); }

// PUBLIC SLOTS
void ObjStyleWidget::setPointSize(float val)
{
    if ((OBJ_STYLE_WIDGET_POINTS & _flags) != 0)
        _points[0]->setValue(val);
}

void ObjStyleWidget::setPointColor(float val[3])
{ setPointColor(val[0], val[1], val[2]); }

void ObjStyleWidget::setPointColor(float r, float g, float b)
{
    if ((OBJ_STYLE_WIDGET_POINTS & _flags) != 0){
        _points[1]->setValue(r);
        _points[2]->setValue(g);
        _points[3]->setValue(b);
    }
}

void ObjStyleWidget::setPointColorRed(float val)
{
    if ((OBJ_STYLE_WIDGET_POINTS & _flags) != 0)
        _points[1]->setValue(val);
}

void ObjStyleWidget::setPointColorGreen(float val)
{
    if ((OBJ_STYLE_WIDGET_POINTS & _flags) != 0)
        _points[2]->setValue(val);
}

void ObjStyleWidget::setPointColorBlue(float val)
{
    if ((OBJ_STYLE_WIDGET_POINTS & _flags) != 0)
        _points[3]->setValue(val);
}

void ObjStyleWidget::setPointOnOff(bool on)
{
    if ((OBJ_STYLE_WIDGET_POINTS & _flags) != 0)
        _points_b->setChecked(on);
}


void ObjStyleWidget::setEdgeWidth(float val)
{
    if ((OBJ_STYLE_WIDGET_EDGES & _flags) != 0)
        _edges[0]->setValue(val);
}

void ObjStyleWidget::setEdgeColor(float val[3])
{ setEdgeColor(val[0], val[1], val[2]); }

void ObjStyleWidget::setEdgeColor(float r, float g, float b)
{
    if ((OBJ_STYLE_WIDGET_EDGES & _flags) != 0){
        _edges[1]->setValue(r);
        _edges[2]->setValue(g);
        _edges[3]->setValue(b);
    }
}

void ObjStyleWidget::setEdgeColorRed(float val)
{
    if ((OBJ_STYLE_WIDGET_EDGES & _flags) != 0)
        _edges[1]->setValue(val);
}

void ObjStyleWidget::setEdgeColorGreen(float val)
{
    if ((OBJ_STYLE_WIDGET_EDGES & _flags) != 0)
        _edges[2]->setValue(val);
}

void ObjStyleWidget::setEdgeColorBlue(float val)
{
    if ((OBJ_STYLE_WIDGET_EDGES & _flags) != 0)
        _edges[3]->setValue(val);
}

void ObjStyleWidget::setEdgeOnOff(bool on)
{
    if ((OBJ_STYLE_WIDGET_EDGES & _flags) != 0)
        _edges_b->setChecked(on);
}



void ObjStyleWidget::setFaceColor(float val[3])
{ setFaceColor(val[0], val[1], val[2]); }

void ObjStyleWidget::setFaceColor(float r, float g, float b)
{
    if ((OBJ_STYLE_WIDGET_FACES & _flags) != 0){
        _faces[0]->setValue(r);
        _faces[1]->setValue(g);
        _faces[2]->setValue(b);
    }
}

void ObjStyleWidget::setFaceColorRed(float val)
{
    if ((OBJ_STYLE_WIDGET_FACES & _flags) != 0)
        _faces[0]->setValue(val);
}

void ObjStyleWidget::setFaceColorGreen(float val)
{
    if ((OBJ_STYLE_WIDGET_FACES & _flags) != 0)
        _faces[1]->setValue(val);
}

void ObjStyleWidget::setFaceColorBlue(float val)
{
    if ((OBJ_STYLE_WIDGET_FACES & _flags) != 0)
        _faces[2]->setValue(val);
}

void ObjStyleWidget::setFaceOnOff(bool on)
{
    if ((OBJ_STYLE_WIDGET_FACES & _flags) != 0)
        _faces_b->setChecked(on);
}



};
