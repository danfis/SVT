#ifndef _CONFIG_DIALOG_HPP_
#define _CONFIG_DIALOG_HPP_

#include <QDialog>
#include "viewer_with_config_dialog.hpp"

/**
 * Dialog which provides configuration of all Objects managed by viewer
 */
class ConfigDialog : public QDialog {
  private:
    ViewerWithConfigDialog *_viewer;

    /**
     * Build controls for each Object
     */
    QWidget *_buildObj(ObjData *, QString name = "");
  public:
    ConfigDialog(ViewerWithConfigDialog *viewer);
    virtual ~ConfigDialog(){}
};
#endif
