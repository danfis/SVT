#ifndef QT_OBJ_WIDGET_HPP
#define QT_OBJ_WIDGET_HPP

#include <QGroupBox>
#include <QPushButton>
#include <QString>

#include "../common/obj.hpp"

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
