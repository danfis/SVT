#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QLabel>

#include "style_dialog.hpp"
#include "style_dialog.moc"
#include "viewer.hpp"
#include "msg.hpp"

void StyleDialog::lock()
{
    _viewer->lock();
    SoDB::writelock();
}

void StyleDialog::unlock()
{
    _viewer->unlock();
    SoDB::writeunlock();
}


StyleDialog::StyleDialog(QWidget *parent, Viewer *viewer, ObjData *data)
    : QDialog(parent), _data(data), _viewer(viewer)
{
    QVBoxLayout *vlayout = new QVBoxLayout;
   
    // points:
    vlayout->addWidget(_buildPoints());
    
    this->setLayout(vlayout);
    resize(200, 200);
}

QWidget *StyleDialog::_buildPoints()
{
    QVBoxLayout *vlayout;
    QHBoxLayout *hlayout;
    QLabel *label;
    QDoubleSpinBox *spin;
    QGroupBox *box;
    QPushButton *button;
   
    vlayout = new QVBoxLayout;

    label = new QLabel("Size");
    vlayout->addWidget(label);
    spin = new QDoubleSpinBox();
    spin->setSingleStep(0.1);
    spin->setRange(1, 10);
    spin->setValue(_data->style_points->pointSize.getValue());
    vlayout->addWidget(spin);
    connect(spin, SIGNAL(valueChanged(double)),
            this, SLOT(changePointsSize(double)));

    label = new QLabel("Diffuse Color");
    vlayout->addWidget(label);
    hlayout = new QHBoxLayout;

    spin = new QDoubleSpinBox;
    spin->setSingleStep(0.05);
    spin->setRange(0, 1);
    spin->setValue(_data->material_points->diffuseColor[0][0]);
    hlayout->addWidget(spin);
    connect(spin, SIGNAL(valueChanged(double)),
            this, SLOT(changePointsDiffuseColorRed(double)));

    spin = new QDoubleSpinBox;
    spin->setSingleStep(0.05);
    spin->setRange(0, 1);
    spin->setValue(_data->material_points->diffuseColor[0][1]);
    hlayout->addWidget(spin);
    connect(spin, SIGNAL(valueChanged(double)),
            this, SLOT(changePointsDiffuseColorGreen(double)));

    spin = new QDoubleSpinBox;
    spin->setSingleStep(0.05);
    spin->setRange(0, 1);
    spin->setValue(_data->material_points->diffuseColor[0][2]);
    hlayout->addWidget(spin);
    connect(spin, SIGNAL(valueChanged(double)),
            this, SLOT(changePointsDiffuseColorBlue(double)));

    vlayout->addLayout(hlayout);

    button = new QPushButton("On/Off");
    button->setCheckable(true);
    if (_data->sw_points->whichChild.getValue() != SO_SWITCH_ALL)
        button->setChecked(true);
    vlayout->addWidget(button);
    connect(button, SIGNAL(clicked(bool)),
            this, SLOT(turnOnOffPoints(bool)));

    box = new QGroupBox("Points", this);
    box->setLayout(vlayout);

    return box;
}

void StyleDialog::changePointsSize(double val)
{
    lock();
    _data->style_points->pointSize = val;
    unlock();
}
void StyleDialog::changePointsDiffuseColorRed(double val)
{
    lock();
    SbColor color = _data->material_points->diffuseColor[0];
    color[0] = val;
    _data->material_points->diffuseColor.setValue(color);
    unlock();
}
void StyleDialog::changePointsDiffuseColorGreen(double val)
{
    lock();
    SbColor color = _data->material_points->diffuseColor[0];
    color[1] = val;
    _data->material_points->diffuseColor.setValue(color);
    unlock();
}
void StyleDialog::changePointsDiffuseColorBlue(double val)
{
    lock();
    SbColor color = _data->material_points->diffuseColor[0];
    color[2] = val;
    _data->material_points->diffuseColor.setValue(color);
    unlock();
}
void StyleDialog::turnOnOffPoints(bool pressed)
{
    lock();
    if (pressed){
        _data->sw_points->whichChild = SO_SWITCH_NONE;
    }else{
        _data->sw_points->whichChild = SO_SWITCH_ALL;
    }
    unlock();
}




StylePushButton::StylePushButton(Viewer *viewer, ObjData *data)
        : QPushButton((QWidget *)viewer), _parent((QWidget *)viewer),
          _viewer(viewer), _data(data)
{
    connect(this, SIGNAL(clicked()), this, SLOT(showDialog()));
}
void StylePushButton::showDialog()
{
    StyleDialog dialog(_parent, _viewer, _data);
    dialog.exec();
}
