#ifndef _VIEWER_PUSH_BUTTON_H_
#define _VIEWER_PUSH_BUTTON_H_

#include <QPushButton>
#include <Inventor/nodes/SoSwitch.h>

class Viewer;

typedef void (*TogglePushButtonCallback)(bool pressed, Viewer *,
                                         void *closure);

/**
 * PushButton which provides functionality of toggle/released button.
 */
class TogglePushButton : public QPushButton {
    Q_OBJECT

  private:
    Viewer *_viewer; /*! pointer to Viewer object */
    TogglePushButtonCallback _callback;
    void *_closure;

  private slots:
    void callCallback();

  public:
    TogglePushButton(Viewer *, TogglePushButtonCallback, void *closure = NULL,
                     const char *text = NULL);
    ~TogglePushButton();
};
#endif
