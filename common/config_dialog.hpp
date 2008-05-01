#ifndef _CONFIG_DIALOG_HPP_
#define _CONFIG_DIALOG_HPP_

#include <QDialog>
#include "viewer.hpp"

/**
 * Dialog which provides configuration of all Objects managed by viewer
 */
class ConfigDialog : public QDialog {
  private:
    Viewer *_viewer;

    /**
     * Build controls for each Object
     */
    QWidget *_buildObj(ObjData *, QString name = "");
  public:
    ConfigDialog(Viewer *viewer);
    virtual ~ConfigDialog(){}
};
#endif
