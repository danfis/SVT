#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QLabel>

#include "default_style_dialog.hpp"
#include "viewer.hpp"
#include "msg.hpp"


#include "default_style_dialog.moc"



DefaultStyleDialog::DefaultStyleDialog(QWidget *parent, Viewer *viewer)
    : QDialog(parent), _viewer(viewer)
{
    QVBoxLayout *vlayout = new QVBoxLayout;
   
    // points:
    vlayout->addWidget(_buildPoints());
    vlayout->addWidget(_buildEdges());
    vlayout->addWidget(_buildFaces());
    
    this->setLayout(vlayout);

    setModal(false);
    resize(200, 200);
}

#define BUILD_PRE \
    QVBoxLayout *vlayout; \
    QHBoxLayout *hlayout; \
    QLabel *label; \
    QDoubleSpinBox *spin; \
    QGroupBox *box; \
    QPushButton *button; \
    \
    vlayout = new QVBoxLayout
#define BUILD_SIZE(name, slotSize, initValue) \
    label = new QLabel("Size"); \
    vlayout->addWidget(label); \
    spin = new QDoubleSpinBox(); \
    spin->setSingleStep(0.1); \
    spin->setRange(1, 10); \
    spin->setValue(initValue); \
    vlayout->addWidget(spin); \
    connect(spin, SIGNAL(valueChanged(double)), \
            this, SLOT(slotSize(double)))
#define BUILD_COLOR(name, slotColorR, slotColorG, slotColorB, \
                          initValueR, initValueG, initValueB) \
    label = new QLabel("Diffuse Color"); \
    vlayout->addWidget(label); \
    hlayout = new QHBoxLayout; \
    \
    spin = new QDoubleSpinBox; \
    spin->setSingleStep(0.05); \
    spin->setRange(0, 1); \
    spin->setValue(initValueR); \
    hlayout->addWidget(spin); \
    connect(spin, SIGNAL(valueChanged(double)), \
            this, SLOT(slotColorR(double))); \
    \
    spin = new QDoubleSpinBox; \
    spin->setSingleStep(0.05); \
    spin->setRange(0, 1); \
    spin->setValue(initValueG); \
    hlayout->addWidget(spin); \
    connect(spin, SIGNAL(valueChanged(double)), \
            this, SLOT(slotColorG(double))); \
    \
    spin = new QDoubleSpinBox; \
    spin->setSingleStep(0.05); \
    spin->setRange(0, 1); \
    spin->setValue(initValueB); \
    hlayout->addWidget(spin); \
    connect(spin, SIGNAL(valueChanged(double)), \
            this, SLOT(slotColorB(double))); \
    \
    vlayout->addLayout(hlayout)

#define BUILD_ON_OFF(name, slotOnOff, initValue) \
    button = new QPushButton("On/Off"); \
    button->setCheckable(true); \
    if (! initValue)\
        button->setChecked(true); \
    vlayout->addWidget(button); \
    connect(button, SIGNAL(clicked(bool)), \
            this, SLOT(slotOnOff(bool)))

#define BUILD_POST(title) \
    box = new QGroupBox(title, this); \
    box->setLayout(vlayout); \
    \
    return box


QWidget *DefaultStyleDialog::_buildPoints()
{
    float size, r, g, b;
    bool on;

    _viewer->defaultPointSize(&size);
    _viewer->defaultPointsDiffuseColor(&r, &g, &b);
    _viewer->defaultPointsSwitch(&on);

    BUILD_PRE;
    BUILD_SIZE(name, changePointsSize, size);
    BUILD_COLOR(points, changePointsDiffuseColorRed,
                        changePointsDiffuseColorGreen,
                        changePointsDiffuseColorBlue,
                        r, g, b);
    BUILD_ON_OFF(points, turnOnOffPoints, on);
    BUILD_POST("Points");
}

QWidget *DefaultStyleDialog::_buildEdges()
{
    float size, r, g, b;
    bool on;

    _viewer->defaultLineWidth(&size);
    _viewer->defaultEdgesDiffuseColor(&r, &g, &b);
    _viewer->defaultEdgesSwitch(&on);

    BUILD_PRE;
    BUILD_SIZE(name, changeEdgesSize, size);
    BUILD_COLOR(edges, changeEdgesDiffuseColorRed,
                        changeEdgesDiffuseColorGreen,
                        changeEdgesDiffuseColorBlue,
                        r, g, b);
    BUILD_ON_OFF(edges, turnOnOffEdges, on);
    BUILD_POST("Edges");
}

QWidget *DefaultStyleDialog::_buildFaces()
{
    float r, g, b;
    bool on;

    _viewer->defaultFacesDiffuseColor(&r, &g, &b);
    _viewer->defaultFacesSwitch(&on);

    BUILD_PRE;
    BUILD_COLOR(faces, changeFacesDiffuseColorRed,
                       changeFacesDiffuseColorGreen,
                       changeFacesDiffuseColorBlue,
                       r, g, b);
    BUILD_ON_OFF(faces, turnOnOffFaces, on);
    BUILD_POST("Faces");
}


#define SIZE_SET(name, attr) \
    lock(); \
    _data->name->attr = val; \
    unlock()

#define COLOR_SET(name, idx) \
    lock(); \
    SbColor color = _data->name->diffuseColor[0]; \
    color[idx] = val; \
    _data->name->diffuseColor.setValue(color); \
    unlock()

#define TURN_ON_OFF(name) \
    lock(); \
    if (pressed){ \
        _data->name->whichChild = SO_SWITCH_NONE; \
    }else{ \
        _data->name->whichChild = SO_SWITCH_ALL; \
    } \
    unlock()

void DefaultStyleDialog::changePointsSize(double val)
{ _viewer->setDefaultPointSize(val); }
void DefaultStyleDialog::changePointsDiffuseColorRed(double val)
{ _viewer->setDefaultPointsDiffuseColorRed(val); }
void DefaultStyleDialog::changePointsDiffuseColorGreen(double val)
{ _viewer->setDefaultPointsDiffuseColorGreen(val); }
void DefaultStyleDialog::changePointsDiffuseColorBlue(double val)
{ _viewer->setDefaultPointsDiffuseColorBlue(val); }
void DefaultStyleDialog::turnOnOffPoints(bool pressed)
{ _viewer->setDefaultPointsSwitch(!pressed); }

void DefaultStyleDialog::changeEdgesSize(double val)
{ _viewer->setDefaultLineWidth(val); }
void DefaultStyleDialog::changeEdgesDiffuseColorRed(double val)
{ _viewer->setDefaultEdgesDiffuseColorRed(val); }
void DefaultStyleDialog::changeEdgesDiffuseColorGreen(double val)
{ _viewer->setDefaultEdgesDiffuseColorGreen(val); }
void DefaultStyleDialog::changeEdgesDiffuseColorBlue(double val)
{ _viewer->setDefaultEdgesDiffuseColorBlue(val); }
void DefaultStyleDialog::turnOnOffEdges(bool pressed)
{ _viewer->setDefaultEdgesSwitch(!pressed); }

void DefaultStyleDialog::changeFacesDiffuseColorRed(double val)
{ _viewer->setDefaultFacesDiffuseColorRed(val); }
void DefaultStyleDialog::changeFacesDiffuseColorGreen(double val)
{ _viewer->setDefaultFacesDiffuseColorGreen(val); }
void DefaultStyleDialog::changeFacesDiffuseColorBlue(double val)
{ _viewer->setDefaultFacesDiffuseColorBlue(val); }
void DefaultStyleDialog::turnOnOffFaces(bool pressed)
{ _viewer->setDefaultFacesSwitch(!pressed); }



DefaultStylePushButton::DefaultStylePushButton(Viewer *viewer,
                                               const QString str)
        : QPushButton(str, (QWidget *)viewer), _parent((QWidget *)viewer),
          _viewer(viewer)
{
    connect(this, SIGNAL(clicked()), this, SLOT(showDialog()));
}
void DefaultStylePushButton::showDialog()
{
    DefaultStyleDialog dialog(_parent, _viewer);
    dialog.exec();
}

