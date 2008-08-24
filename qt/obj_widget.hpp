#ifndef QT_OBJ_HPP
#define QT_OBJ_HPP

#include <QGroupBox>
#include <QPushButton>
#include <QString>

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
    void *_obj;
    ObjWidgetFlags _flags;
    QPushButton *_config, *_on_off;
    QString name;

  private slots:
    void _clickedConfig(bool checked);
    void _clickedOnOff(bool checked);


  public:
    ObjWidget(void *obj, ObjWidgetFlags flags = OBJ_WIDGET_ALL);

  public slots:
    void setName(const char *name);
    void setButtonOnOff(bool checked);

  signals:
    void clickedConfig(void *obj);
    void clickedOnOff(void *obj, bool checked);
};

};

#endif
