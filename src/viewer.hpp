#ifndef _VIEWER_H_
#define _VIEWER_H_

#include <vector>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/threads/SbMutex.h>

#include "viewer_push_button.hpp"

namespace GSRM {

/**
 * Viewer based on SoQtExaminerViewer
 */
class Viewer : public QObject, public SoQtExaminerViewer{
  private:
    SbMutex _lock; /*! internal lock for multithreading */
    std::vector<ViewerPushButton *> _buttons; /*! list of registered buttons */

  protected:
    virtual SbBool processSoEvent(const SoEvent *const event);
    virtual void actualRedraw(void);

  public:
    Viewer(QWidget *parent, const char *name = "");

    /**
     * Lock/Unlock viewer
     */
    int lock() { return _lock.lock(); }
    int unlock() { return _lock.unlock(); }

    /**
     * Add button using which is possible to show/hide given SoSeparator
     */
    void addToggleButton(ViewerPushButtonCallback callback,
                         void *closure = NULL);

    virtual void show();
};

}
#endif
