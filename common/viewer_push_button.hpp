#ifndef _VIEWER_PUSH_BUTTON_H_
#define _VIEWER_PUSH_BUTTON_H_

#include <QPushButton>
#include <Inventor/nodes/SoSwitch.h>

class Viewer;

typedef void (*ViewerPushButtonCallback)(bool pressed, Viewer *,
                                         void *closure);

/**
 * PushButton used by Viewer
 */
class ViewerPushButton : public QPushButton {
    Q_OBJECT

  private:
    Viewer *_viewer; /*! pointer to Viewer object */
    ViewerPushButtonCallback _callback;
    void *_closure;

  private slots:
    void callCallback();

  public:
    ViewerPushButton(Viewer *, ViewerPushButtonCallback, void *closure = NULL,
                     const char *text = NULL);
    ~ViewerPushButton();
};
#endif
