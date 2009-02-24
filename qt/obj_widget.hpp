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

#ifndef QT_OBJ_WIDGET_HPP
#define QT_OBJ_WIDGET_HPP

#include <QGroupBox>
#include <QPushButton>
#include <QString>

#include "common/obj.hpp"

namespace SVT {

namespace Qt {

enum ObjWidgetFlags {
    OBJ_WIDGET_NAME = 0x1,
    OBJ_WIDGET_CONFIG = 0x2,
    OBJ_WIDGET_ON_OFF = 0x4,
    OBJ_WIDGET_ALL = 0xF
};

class ObjWidget : public QGroupBox {
    Q_OBJECT

  private:
    Common::Obj *_obj;
    int _flags;
    QPushButton *_conf, *_on_off;
    QString name;

    void _setUpConnections();
    void _setUpDefaultValues();

  private slots:
    void _config();
    void _onOff(bool checked);


  public:
    ObjWidget(Common::Obj *obj, int flags = OBJ_WIDGET_ALL);

  public slots:
    void setName(const char *name);
    void setButtonOnOff(bool on);

  signals:
    void config(Common::Obj *obj);
    void onOff(Common::Obj *obj, bool on);
};

} /* Qt */

} /* SVT */

#endif
