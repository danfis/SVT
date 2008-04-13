#include "config_dialog.hpp"
#include "viewer_with_config_dialog.hpp"


#include "viewer_with_config_dialog.moc"

ViewerWithConfigDialog::ViewerWithConfigDialog(QWidget *parent, const char *name)
    : Viewer(parent, name), _conf_dialog(0), _conf_button(0)
{
}

void ViewerWithConfigDialog::show()
{
    _setUpConfigDialog();

    Viewer::show();
}

static void ConfigDialogCallback(bool pressed, Viewer *, void *cl);
void ViewerWithConfigDialog::_setUpConfigDialog()
{
    _conf_button = new TogglePushButton((Viewer *)this, ConfigDialogCallback,
                                        (void *)&_conf_dialog);

    addAppPushButton(_conf_button);
}
static void ConfigDialogCallback(bool pressed, Viewer *viewer, void *cl)
{
    ConfigDialog **dialog = (ConfigDialog **)cl;

    if (pressed && *dialog == 0){
        *dialog = new ConfigDialog((ViewerWithConfigDialog *)viewer);
        (*dialog)->show();
        viewer->connect(*dialog, SIGNAL(finished(int)),
                        viewer, SLOT(offConfigDialog(int)));
    }

    if (!pressed && *dialog != 0){
        delete *dialog;
        *dialog = 0;
    }
}

void ViewerWithConfigDialog::offConfigDialog(int)
{
    _conf_dialog = 0;
    _conf_button->setChecked(false);
}
