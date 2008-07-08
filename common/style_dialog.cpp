/**
 * Coin3dTools
 * ------------
 * Copyright (c)2007 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of Coin3dTools
 *
 * Coin3dTools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Coin3dTools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Coin3dTools.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QLabel>

#include "style_dialog.hpp"
#include "viewer.hpp"
#include "msg.hpp"


#include "style_dialog.moc"

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
    : QWidget(parent), _data(data), _viewer(viewer)
{
    QVBoxLayout *vlayout = new QVBoxLayout;
   
    // points:
    vlayout->addWidget(_buildPoints());
    vlayout->addWidget(_buildEdges());
    vlayout->addWidget(_buildFaces());
    
    this->setLayout(vlayout);
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
#define BUILD_SIZE(name, valueMember, slotSize) \
    label = new QLabel("Size"); \
    vlayout->addWidget(label); \
    spin = new QDoubleSpinBox(); \
    spin->setSingleStep(0.1); \
    spin->setRange(1, 10); \
    spin->setValue(_data->style_##name->valueMember.getValue()); \
    vlayout->addWidget(spin); \
    connect(spin, SIGNAL(valueChanged(double)), \
            this, SLOT(slotSize(double)))
#define BUILD_COLOR(name, slotColorR, slotColorG, slotColorB) \
    label = new QLabel("Diffuse Color"); \
    vlayout->addWidget(label); \
    hlayout = new QHBoxLayout; \
    \
    spin = new QDoubleSpinBox; \
    spin->setSingleStep(0.05); \
    spin->setRange(0, 1); \
    spin->setValue(_data->material_##name->diffuseColor[0][0]); \
    hlayout->addWidget(spin); \
    connect(spin, SIGNAL(valueChanged(double)), \
            this, SLOT(slotColorR(double))); \
    \
    spin = new QDoubleSpinBox; \
    spin->setSingleStep(0.05); \
    spin->setRange(0, 1); \
    spin->setValue(_data->material_##name->diffuseColor[0][1]); \
    hlayout->addWidget(spin); \
    connect(spin, SIGNAL(valueChanged(double)), \
            this, SLOT(slotColorG(double))); \
    \
    spin = new QDoubleSpinBox; \
    spin->setSingleStep(0.05); \
    spin->setRange(0, 1); \
    spin->setValue(_data->material_##name->diffuseColor[0][2]); \
    hlayout->addWidget(spin); \
    connect(spin, SIGNAL(valueChanged(double)), \
            this, SLOT(slotColorB(double))); \
    \
    vlayout->addLayout(hlayout)

#define BUILD_ON_OFF(name, slotOnOff) \
    button = new QPushButton("On/Off"); \
    button->setCheckable(true); \
    if (_data->sw_##name->whichChild.getValue() != SO_SWITCH_ALL) \
        button->setChecked(true); \
    vlayout->addWidget(button); \
    connect(button, SIGNAL(clicked(bool)), \
            this, SLOT(slotOnOff(bool)))

#define BUILD_POST(title) \
    box = new QGroupBox(title, this); \
    box->setLayout(vlayout); \
    \
    return box

#define BUILD(name, title, slotSize, slotColorR, slotColorG, slotColorB,\
              slotOnOff) \
    BUILD_PRE; \
    BUILD_SIZE(name, slotSize); \
    BUILD_COLOR(name, slotColorR, slotColorG, slotColorB); \
    BUILD_ON_OFF(name, slotOnOff); \
    BUILD_POST(title);

QWidget *StyleDialog::_buildPoints()
{
    BUILD_PRE;
    BUILD_SIZE(points, pointSize, changePointsSize);
    BUILD_COLOR(points, changePointsDiffuseColorRed,
                changePointsDiffuseColorGreen, changePointsDiffuseColorBlue);
    BUILD_ON_OFF(points, turnOnOffPoints);
    BUILD_POST("Points");
}

QWidget *StyleDialog::_buildEdges()
{
    BUILD_PRE;
    BUILD_SIZE(edges, lineWidth, changeEdgesSize);
    BUILD_COLOR(edges, changeEdgesDiffuseColorRed,
                changeEdgesDiffuseColorGreen, changeEdgesDiffuseColorBlue);
    BUILD_ON_OFF(edges, turnOnOffEdges);
    BUILD_POST("Edges");
}

QWidget *StyleDialog::_buildFaces()
{
    BUILD_PRE;
    BUILD_COLOR(faces, changeFacesDiffuseColorRed,
                changeFacesDiffuseColorGreen, changeFacesDiffuseColorBlue);
    BUILD_ON_OFF(faces, turnOnOffFaces);
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

void StyleDialog::changePointsSize(double val)
{ SIZE_SET(style_points, pointSize); }
void StyleDialog::changePointsDiffuseColorRed(double val)
{ COLOR_SET(material_points, 0); }
void StyleDialog::changePointsDiffuseColorGreen(double val)
{ COLOR_SET(material_points, 1); }
void StyleDialog::changePointsDiffuseColorBlue(double val)
{ COLOR_SET(material_points, 2); }
void StyleDialog::turnOnOffPoints(bool pressed)
{ TURN_ON_OFF(sw_points); }

void StyleDialog::changeEdgesSize(double val)
{ SIZE_SET(style_edges, lineWidth); }
void StyleDialog::changeEdgesDiffuseColorRed(double val)
{ COLOR_SET(material_edges, 0); }
void StyleDialog::changeEdgesDiffuseColorGreen(double val)
{ COLOR_SET(material_edges, 1); }
void StyleDialog::changeEdgesDiffuseColorBlue(double val)
{ COLOR_SET(material_edges, 2); }
void StyleDialog::turnOnOffEdges(bool pressed)
{ TURN_ON_OFF(sw_edges); }

void StyleDialog::changeFacesDiffuseColorRed(double val)
{ COLOR_SET(material_faces, 0); }
void StyleDialog::changeFacesDiffuseColorGreen(double val)
{ COLOR_SET(material_faces, 1); }
void StyleDialog::changeFacesDiffuseColorBlue(double val)
{ COLOR_SET(material_faces, 2); }
void StyleDialog::turnOnOffFaces(bool pressed)
{ TURN_ON_OFF(sw_faces); }




StylePushButton::StylePushButton(Viewer *viewer, ObjData *data,
                                 const QString str)
        : QPushButton(str, (QWidget *)viewer), _parent((QWidget *)viewer),
          _viewer(viewer), _data(data)
{
    connect(this, SIGNAL(clicked()), this, SLOT(showDialogInternal()));
}
void StylePushButton::showDialogInternal()
{
    emit showDialog(new StyleDialog(_parent, _viewer, _data));
}
