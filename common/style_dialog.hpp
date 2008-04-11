#ifndef _STYLE_WINDOW_HPP_
#define _STYLE_WINDOW_HPP_

#include <QDialog>
#include <QPushButton>

class StyleDialog : public QDialog {
  public:
    StyleDialog(QWidget *parent = 0);
    virtual ~StyleDialog(){}
};

class StylePushButton : public QPushButton {
    Q_OBJECT

  private:
    QWidget *_parent;

  public:
    StylePushButton(QWidget *parent = 0);
    ~StylePushButton(){}

  private slots:
    void showDialog();
};
#endif
