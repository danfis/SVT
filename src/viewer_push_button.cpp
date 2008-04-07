#include "viewer_push_button.hpp"
#include "viewer.hpp"
using namespace std;

#include "viewer_push_button.moc"

GSRM::ViewerPushButton::ViewerPushButton(Viewer *v,
                     ViewerPushButtonCallback callback, void *closure,
                     const char *text)
    : QPushButton(text), _viewer(v), _callback(callback),
      _closure(closure)
{
    setCheckable(true);
    connect(this, SIGNAL(clicked()), this, SLOT(callCallback()));
}

GSRM::ViewerPushButton::~ViewerPushButton()
{
}

void GSRM::ViewerPushButton::callCallback()
{
    _callback(isChecked(), _viewer, _closure);
}
