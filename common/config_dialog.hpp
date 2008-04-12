#ifndef _CONFIG_DIALOG_HPP_
#define _CONFIG_DIALOG_HPP_

#include <QDialog>
#include "viewer.hpp"

class ConfigDialog : public QDialog {
  private:
    Viewer *_viewer;

    QWidget *_buildObj(ObjData *, QString name = "");
  public:
    ConfigDialog(Viewer *viewer);
    virtual ~ConfigDialog(){}
};
#endif
