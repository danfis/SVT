#ifndef _VIEWER_ADV_HPP_
#define _VIEWER_ADV_HPP_

#include "viewer.hpp"
#include "toggle_push_button.hpp"

class ConfigDialog;


class ViewerWithConfigDialog : public Viewer {
    Q_OBJECT

  protected:
    ConfigDialog *_conf_dialog; /*! holds pointer to shown ConfigDialog
                                    or 0 (if no ConfigDialog is shown) */
    TogglePushButton *_conf_button; /*! button using which is possible to
                                        show/hide ConfigDialog */

    virtual void _setUpConfigDialog();

    friend class ConfigDialog;
  protected slots:
    /**
     * Slot used by _conf_button and _conf_dialog
     */
    void offConfigDialog(int);

  public:
    ViewerWithConfigDialog(QWidget *parent, const char *name = "");
    void show();
};
#endif

