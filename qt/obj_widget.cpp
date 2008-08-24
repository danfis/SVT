#include "obj_widget.hpp"
#include <QVBoxLayout>

#include "obj_widget.moc"

namespace Qt {

ObjWidget::ObjWidget(void *obj, ObjWidgetFlags flags)
    : _obj(obj), _flags(flags), _config(0), _on_off(0)
{
    QVBoxLayout *layout = new QVBoxLayout;

    if ((OBJ_WIDGET_ON_OFF & flags) != 0){
        _on_off = new QPushButton("On / Off");
        _on_off->setCheckable(true);

        layout->addWidget(_on_off);
    }

    if ((OBJ_WIDGET_CONFIG & flags) != 0){
        _config = new QPushButton("Config");
        
        layout->addWidget(_config);
    }

    setLayout(layout);
}

void ObjWidget::_clickedConfig(bool checked)
{
    emit clickedConfig(_obj);
}

void ObjWidget::_clickedOnOff(bool checked)
{
    emit clickedOnOff(_obj, checked);
}

void ObjWidget::setName(const char *name)
{
    if ((OBJ_WIDGET_NAME & _flags) != 0){
        setTitle(name);
    }
}

void ObjWidget::setButtonOnOff(bool checked)
{
    if (_on_off != 0){
        _on_off->setChecked(checked);
    }
}


};
