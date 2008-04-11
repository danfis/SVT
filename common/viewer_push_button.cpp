#include "viewer_push_button.hpp"
#include "viewer.hpp"
using namespace std;

#include "viewer_push_button.moc"

ViewerPushButton::ViewerPushButton(Viewer *v,
                     ViewerPushButtonCallback callback, void *closure,
                     const char *text)
    : QPushButton(text), _viewer(v), _callback(callback),
      _closure(closure)
{
    setCheckable(true);
    connect(this, SIGNAL(clicked()), this, SLOT(callCallback()));
}

ViewerPushButton::~ViewerPushButton()
{
}

void ViewerPushButton::callCallback()
{
    _callback(isChecked(), _viewer, _closure);
}
