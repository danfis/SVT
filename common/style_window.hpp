#ifndef _STYLE_WINDOW_HPP_
#define _STYLE_WINDOW_HPP_

#include <QDockWidget>

class StyleWindow : public QDockWidget {
  public:
    StyleWindow(const QString &title, QWidget *parent = 0);
    StyleWindow(QWidget *parent = 0);
    virtual ~StyleWindow(){}
};
#endif
