#include "toggle_push_button.hpp"
#include "toggle_push_button.moc"
#include "viewer.hpp"

TogglePushButton::TogglePushButton(Viewer *v,
                     TogglePushButtonCallback callback, void *closure,
                     const char *text)
    : QPushButton(text), _viewer(v), _callback(callback),
      _closure(closure)
{
    setCheckable(true);
    connect(this, SIGNAL(clicked()), this, SLOT(callCallback()));
}

TogglePushButton::~TogglePushButton()
{
}

void TogglePushButton::callCallback()
{
    _callback(isChecked(), _viewer, _closure);
}
