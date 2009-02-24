/**
 * SVT
 * ----------
 * Copyright (c)2007,2008,2009 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of SVT
 *
 * SVT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SVT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SVT. If not, see <http://www.gnu.org/licenses/>.
 */

#include "obj_widget.hpp"
#include <QVBoxLayout>

#include "obj_widget.moc"

namespace SVT {

namespace Qt {

ObjWidget::ObjWidget(Common::Obj *obj, int flags)
    : _obj(obj), _flags(flags), _conf(0), _on_off(0)
{
    QVBoxLayout *layout = new QVBoxLayout;

    if ((OBJ_WIDGET_ON_OFF & flags) != 0){
        _on_off = new QPushButton("On / Off");
        _on_off->setCheckable(true);

        layout->addWidget(_on_off);
    }

    if ((OBJ_WIDGET_CONFIG & flags) != 0){
        _conf = new QPushButton("Config");
        
        layout->addWidget(_conf);
    }

    setLayout(layout);

    _setUpConnections();
    _setUpDefaultValues();

}

void ObjWidget::_setUpConnections()
{
    if ((OBJ_WIDGET_ON_OFF & _flags) != 0){
        connect(_on_off, SIGNAL(toggled(bool)),
                this, SLOT(_onOff(bool)));
    }

    if ((OBJ_WIDGET_CONFIG & _flags) != 0){
        connect(_conf, SIGNAL(clicked()),
                this, SLOT(_config()));
    }
}

void ObjWidget::_setUpDefaultValues()
{
    if (_obj->name().size() > 0){
        setName(_obj->name().c_str());
    }else{
        /* TODO */
    }

    if (_on_off != 0){
        setButtonOnOff(_obj->allOn());
    }
}

void ObjWidget::_config()
{
    emit config(_obj);
}

void ObjWidget::_onOff(bool checked)
{
    _obj->setAllOn(!checked);

    emit onOff(_obj, !checked);
}

void ObjWidget::setName(const char *name)
{
    if ((OBJ_WIDGET_NAME & _flags) != 0){
        setTitle(name);
    }
}

void ObjWidget::setButtonOnOff(bool on)
{
    if (_on_off != 0){
        _on_off->setChecked(!on);
    }
}


} /* Qt */

} /* SVT */
