#include <list>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QScrollArea>
#include "config_dialog.hpp"
#include "style_dialog.hpp"
#include "toggle_push_button.hpp"


ConfigDialog::ConfigDialog(Viewer *viewer)
    : QDialog((QWidget *)viewer,
              Qt::Dialog | Qt::SubWindow | Qt::WindowStaysOnTopHint),
      _viewer(viewer)
{
    std::list<ObjData *>::iterator it, it_end;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(10);

    it = _viewer->_objects.begin();
    it_end= _viewer->_objects.end();
    for (int i=1; it != it_end; it++, i++){
        layout->addWidget(_buildObj(*it, QString("Object %1").arg(i)));
    }

    QGroupBox *box = new QGroupBox("Objects");
    box->setFlat(true);
    layout->setContentsMargins(0, 0, 0, 0);
    box->setLayout(layout);

    QScrollArea *area = new QScrollArea;
    area->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    area->setLineWidth(0);
    area->setFrameShape(QFrame::NoFrame);
    area->setContentsMargins(0, 0, 0, 0);
    area->setWidget(box);
    layout = new QVBoxLayout;
    layout->addWidget(area);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    setModal(false);
    resize(130, 300);
}

static void ObjDataButtonCallback(bool pressed, Viewer *viewer, void *cl);

QWidget *ConfigDialog::_buildObj(ObjData *data, QString name)
{
    QVBoxLayout *layout = new QVBoxLayout;

    TogglePushButton *button = new TogglePushButton(_viewer,
                                                    ObjDataButtonCallback,
                                                    (void *)data->sw,
                                                    "On/Off");
    if (data->sw->whichChild.getValue() != SO_SWITCH_ALL)
        button->setChecked(true);
    layout->addWidget(button);

    StylePushButton *style = new StylePushButton(_viewer, data, "Config");
    layout->addWidget(style);

    QGroupBox *box = new QGroupBox(name);
    box->setLayout(layout);

    return box;
}

static void ObjDataButtonCallback(bool pressed, Viewer *viewer, void *cl)
{
    SoSwitch *sw = (SoSwitch *)cl;

    SoDB::writelock();
    viewer->lock();
    if (pressed){
        sw->whichChild = SO_SWITCH_NONE;
    }else{
        sw->whichChild = SO_SWITCH_ALL;
    }
    viewer->unlock();
    SoDB::writeunlock();
}
