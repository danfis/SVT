#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "obj_style_widget.hpp"

#include "obj_style_widget.moc"

namespace SVT {

namespace Qt {

ObjStyleWidget::ObjStyleWidget(Common::Obj *obj)
    : _obj(obj)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setAlignment(::Qt::AlignTop | ::Qt::AlignHCenter);

    _points[0] = _points[1] = _points[2] = _points[3] = 0;
    _points_b = 0;
    _edges[0] = _edges[1] = _edges[2] = _edges[3] = 0;
    _edges_b = 0;
    _faces[0] = _faces[1] = _faces[2] = 0;
    _faces_b = 0;

    if (_obj->numPoints() > 0){
        layout->addWidget(_buildPoints());
    }
    if (_obj->numEdges() > 0){
        layout->addWidget(_buildEdges());
    }
    if (_obj->numFaces() > 0){
        layout->addWidget(_buildFaces());
    }

    layout->addStretch(1);

    setLayout(layout);

    _setUpConnections();
    _setUpDefaultValues();
}

void ObjStyleWidget::_setUpConnections()
{
    if (_points[0] != 0){
        connect(_points[0], SIGNAL(valueChanged(double)),
                this, SLOT(_pointSize(double)));
        connect(_points[1], SIGNAL(valueChanged(double)),
                this, SLOT(_pointColorRed(double)));
        connect(_points[2], SIGNAL(valueChanged(double)),
                this, SLOT(_pointColorGreen(double)));
        connect(_points[3], SIGNAL(valueChanged(double)),
                this, SLOT(_pointColorBlue(double)));
        connect(_points_b, SIGNAL(toggled(bool)),
                this, SLOT(_pointOnOff(bool)));
    }


    if (_edges[0] != 0){
        connect(_edges[0], SIGNAL(valueChanged(double)),
                this, SLOT(_edgeWidth(double)));
        connect(_edges[1], SIGNAL(valueChanged(double)),
                this, SLOT(_edgeColorRed(double)));
        connect(_edges[2], SIGNAL(valueChanged(double)),
                this, SLOT(_edgeColorGreen(double)));
        connect(_edges[3], SIGNAL(valueChanged(double)),
                this, SLOT(_edgeColorBlue(double)));
        connect(_edges_b, SIGNAL(toggled(bool)),
                this, SLOT(_edgeOnOff(bool)));
    }

    if (_faces[0] != 0){
        connect(_faces[0], SIGNAL(valueChanged(double)),
                this, SLOT(_faceColorRed(double)));
        connect(_faces[1], SIGNAL(valueChanged(double)),
                this, SLOT(_faceColorGreen(double)));
        connect(_faces[2], SIGNAL(valueChanged(double)),
                this, SLOT(_faceColorBlue(double)));
        connect(_faces_b, SIGNAL(toggled(bool)),
                this, SLOT(_faceOnOff(bool)));
    }
}

void ObjStyleWidget::_setUpDefaultValues()
{
    float r, g, b;

    if (_points[0] != 0){
        setPointSize(_obj->pointSize());
        _obj->pointColor(&r, &g, &b);
        setPointColor(r, g, b);
        setPointOnOff(_obj->pointsOn());
    }

    if (_edges[0] != 0){
        setEdgeWidth(_obj->edgeWidth());
        _obj->edgeColor(&r, &g, &b);
        setEdgeColor(r, g, b);
        setEdgeOnOff(_obj->edgesOn());
    }

    if (_faces[0] != 0){
        _obj->faceColor(&r, &g, &b);
        setFaceColor(r, g, b);
        setFaceOnOff(_obj->facesOn());
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
    refs[1] = spin;
    hlayout->addWidget(spin);

    spin = new QDoubleSpinBox;
    spin->setRange(0, 1);
    spin->setSingleStep(0.05);
    refs[2] = spin;
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
void ObjStyleWidget::_pointSize(double val)
{ 
    _obj->setPointSize((float)val);

    emit pointSize(_obj, val);
}

void ObjStyleWidget::_pointColorRed(double val)
{
    _obj->setPointColorRed((float)val);

    emit pointColorRed(_obj, val);
    emit pointColor(_obj,
                    _points[1]->value(),
                    _points[2]->value(),
                    _points[3]->value());
}

void ObjStyleWidget::_pointColorBlue(double val)
{
    _obj->setPointColorBlue((float)val);

    emit pointColorBlue(_obj, val);
    emit pointColor(_obj,
                    _points[1]->value(),
                    _points[2]->value(),
                    _points[3]->value());
}

void ObjStyleWidget::_pointColorGreen(double val)
{
    _obj->setPointColorGreen((float)val);

    emit pointColorGreen(_obj, val);
    emit pointColor(_obj,
                    _points[1]->value(),
                    _points[2]->value(),
                    _points[3]->value());
}

void ObjStyleWidget::_pointOnOff(bool off)
{
    _obj->setPointsOn(!off);

    emit pointOnOff(_obj, !off);
}

void ObjStyleWidget::_edgeWidth(double val)
{
    _obj->setEdgeWidth((float)val);

    emit edgeWidth(_obj, val);
}

void ObjStyleWidget::_edgeColorRed(double val)
{
    _obj->setEdgeColorRed((float)val);

    emit edgeColorRed(_obj, val);
    emit edgeColor(_obj,
                   _edges[1]->value(),
                   _edges[2]->value(),
                   _edges[3]->value());
}

void ObjStyleWidget::_edgeColorBlue(double val)
{
    _obj->setEdgeColorBlue((float)val);

    emit edgeColorBlue(_obj, val);
    emit edgeColor(_obj,
                   _edges[1]->value(),
                   _edges[2]->value(),
                   _edges[3]->value());
}

void ObjStyleWidget::_edgeColorGreen(double val)
{
    _obj->setEdgeColorGreen((float)val);

    emit edgeColorGreen(_obj, val);
    emit edgeColor(_obj,
                   _edges[1]->value(),
                   _edges[2]->value(),
                   _edges[3]->value());
}

void ObjStyleWidget::_edgeOnOff(bool off)
{
    _obj->setEdgesOn(!off);

    emit edgeOnOff(_obj, !off);
}

void ObjStyleWidget::_faceColorRed(double val)
{
    _obj->setFaceColorRed((float)val);

    emit faceColorRed(_obj, val);
    emit faceColor(_obj,
                   _faces[0]->value(),
                   _faces[1]->value(),
                   _faces[2]->value());
}

void ObjStyleWidget::_faceColorBlue(double val)
{
    _obj->setFaceColorBlue((float)val);

    emit faceColorBlue(_obj, val);
    emit faceColor(_obj,
                   _faces[0]->value(),
                   _faces[1]->value(),
                   _faces[2]->value());
}

void ObjStyleWidget::_faceColorGreen(double val)
{
    _obj->setFaceColorGreen((float)val);

    emit faceColorGreen(_obj, val);
    emit faceColor(_obj,
                   _faces[0]->value(),
                   _faces[1]->value(),
                   _faces[2]->value());
}

void ObjStyleWidget::_faceOnOff(bool off)
{
    _obj->setFacesOn(!off);

    emit faceOnOff(_obj, !off);
}

// PUBLIC SLOTS
void ObjStyleWidget::setPointSize(double val)
{
    if (_points[0] != 0)
        _points[0]->setValue(val);
}

void ObjStyleWidget::setPointColor(double val[3])
{ setPointColor(val[0], val[1], val[2]); }

void ObjStyleWidget::setPointColor(double r, double g, double b)
{
    if (_points[1] != 0){
        _points[1]->setValue(r);
        _points[2]->setValue(g);
        _points[3]->setValue(b);
    }
}

void ObjStyleWidget::setPointColorRed(double val)
{
    if (_points[1] != 0)
        _points[1]->setValue(val);
}

void ObjStyleWidget::setPointColorGreen(double val)
{
    if (_points[2] != 0)
        _points[2]->setValue(val);
}

void ObjStyleWidget::setPointColorBlue(double val)
{
    if (_points[3] != 0)
        _points[3]->setValue(val);
}

void ObjStyleWidget::setPointOnOff(bool on)
{
    if (_points_b != 0)
        _points_b->setChecked(!on);
}


void ObjStyleWidget::setEdgeWidth(double val)
{
    if (_edges[0] != 0)
        _edges[0]->setValue(val);
}

void ObjStyleWidget::setEdgeColor(double val[3])
{ setEdgeColor(val[0], val[1], val[2]); }

void ObjStyleWidget::setEdgeColor(double r, double g, double b)
{
    if (_edges[1] != 0){
        _edges[1]->setValue(r);
        _edges[2]->setValue(g);
        _edges[3]->setValue(b);
    }
}

void ObjStyleWidget::setEdgeColorRed(double val)
{
    if (_edges[1] != 0)
        _edges[1]->setValue(val);
}

void ObjStyleWidget::setEdgeColorGreen(double val)
{
    if (_edges[2] != 0)
        _edges[2]->setValue(val);
}

void ObjStyleWidget::setEdgeColorBlue(double val)
{
    if (_edges[3] != 0)
        _edges[3]->setValue(val);
}

void ObjStyleWidget::setEdgeOnOff(bool on)
{
    if (_edges_b != 0)
        _edges_b->setChecked(!on);
}



void ObjStyleWidget::setFaceColor(double val[3])
{ setFaceColor(val[0], val[1], val[2]); }

void ObjStyleWidget::setFaceColor(double r, double g, double b)
{
    if (_faces[0] != 0){
        _faces[0]->setValue(r);
        _faces[1]->setValue(g);
        _faces[2]->setValue(b);
    }
}

void ObjStyleWidget::setFaceColorRed(double val)
{
    if (_faces[0] != 0)
        _faces[0]->setValue(val);
}

void ObjStyleWidget::setFaceColorGreen(double val)
{
    if (_faces[1] != 0)
        _faces[1]->setValue(val);
}

void ObjStyleWidget::setFaceColorBlue(double val)
{
    if (_faces[2] != 0)
        _faces[2]->setValue(val);
}

void ObjStyleWidget::setFaceOnOff(bool on)
{
    if (_faces_b != 0)
        _faces_b->setChecked(!on);
}



} /* Qt */

} /* SVT */
