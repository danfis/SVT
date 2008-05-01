#include <list>
#include <QVBoxLayout>
#include <QGroupBox>
#include "config_dialog.hpp"
#include "style_dialog.hpp"
#include "default_style_dialog.hpp"
#include "toggle_push_button.hpp"


#include "config_dialog.moc"

ConfigDialog::ConfigDialog(Viewer *viewer)
    : QScrollArea((QWidget *)viewer),
              //Qt::Dialog | Qt::SubWindow | Qt::WindowStaysOnTopHint),
      _viewer(viewer)
{
    std::list<ObjData *>::iterator it, it_end;

    QWidget *inside = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(10);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(_buildDefaultStyle("Default Style"));

    it = _viewer->_objects.begin();
    it_end= _viewer->_objects.end();
    for (int i=1; it != it_end; it++, i++){
        layout->addWidget(_buildObj(*it, QString("Object %1").arg(i)));
    }
    inside->setLayout(layout);

    setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    setLineWidth(0);
    setFrameShape(QFrame::NoFrame);
    setContentsMargins(0, 0, 0, 0);
    setWidget(inside);
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
    connect(style, SIGNAL(showDialog(QWidget *)),
            this, SLOT(showWidgetSlot(QWidget *)));
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


QWidget *ConfigDialog::_buildDefaultStyle(QString title)
{
    QVBoxLayout *layout = new QVBoxLayout;

    DefaultStylePushButton *style = new DefaultStylePushButton(_viewer, "Config");
    connect(style, SIGNAL(showDialog(QWidget *)),
            this, SLOT(showWidgetSlot(QWidget *)));
    layout->addWidget(style);

    QGroupBox *box = new QGroupBox(title);
    box->setLayout(layout);

    return box;
}
