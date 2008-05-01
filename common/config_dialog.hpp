#ifndef _CONFIG_DIALOG_HPP_
#define _CONFIG_DIALOG_HPP_

#include <QScrollArea>
#include "viewer.hpp"

/**
 * Dialog which provides configuration of all Objects managed by viewer
 */
class ConfigDialog : public QScrollArea {
    Q_OBJECT

  private:
    Viewer *_viewer;

    /**
     * Build controls for each Object
     */
    QWidget *_buildObj(ObjData *, QString name = "");
    QWidget *_buildDefaultStyle(QString title = "");

  private slots:
    void showWidgetSlot(QWidget *widg)
        { emit showWidget(widg); }
  public:
    ConfigDialog(Viewer *viewer);
    virtual ~ConfigDialog(){}

  signals:
    void showWidget(QWidget *widg);
};
#endif
