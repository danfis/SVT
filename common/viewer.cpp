#include <iostream>
#include <QVBoxLayout>
#include "viewer.hpp"
using namespace std;

GSRM::Viewer::Viewer(QWidget *parent, const char *name)
    : SoQtExaminerViewer(parent, name)
{
}


void GSRM::Viewer::addToggleButton(ViewerPushButtonCallback callback,
                                   void *closure)
{
    ViewerPushButton *button = new ViewerPushButton(this, callback,
                                                    closure);
    _buttons.push_back(button);
    addAppPushButton(button);
}

SbBool GSRM::Viewer::processSoEvent(const SoEvent *const event)
{
    SbBool ret;

    lock();
    ret = SoQtExaminerViewer::processSoEvent(event);
    unlock();

    return ret;
}
void GSRM::Viewer::actualRedraw(void)
{
    lock();
    SoQtExaminerViewer::actualRedraw();
    unlock();
}

void GSRM::Viewer::show()
{
    // set up properly alignment to top
    QWidget *parent = SoQtExaminerViewer::getAppPushButtonParent();
    QLayout *layout;
    if (parent != NULL){
        layout = parent->layout();
        if (layout == NULL){
            layout = new QVBoxLayout;
            parent->setLayout(layout);
        }
        layout->setAlignment(Qt::AlignTop);
    }

    SoQtExaminerViewer::show();
}
