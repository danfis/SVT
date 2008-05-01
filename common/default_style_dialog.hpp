#ifndef _DEFAULT_STYLE_WINDOW_HPP_
#define _DEFAULT_STYLE_WINDOW_HPP_

#include <QDialog>
#include <QPushButton>
#include "objdata.hpp"

class Viewer;

/**
 * Class which provides dialog for configuring of properties(style) of one
 * ObjData object.
 */
class DefaultStyleDialog : public QWidget {
    Q_OBJECT

  private:
    Viewer *_viewer;

    QWidget *_buildPoints();
    QWidget *_buildEdges();
    QWidget *_buildFaces();

    void lock();
    void unlock();
  private slots:
    void changePointsSize(double val);
    void changePointsDiffuseColorRed(double val);
    void changePointsDiffuseColorGreen(double val);
    void changePointsDiffuseColorBlue(double val);
    void turnOnOffPoints(bool pressed);
    void changeEdgesSize(double val);
    void changeEdgesDiffuseColorRed(double val);
    void changeEdgesDiffuseColorGreen(double val);
    void changeEdgesDiffuseColorBlue(double val);
    void turnOnOffEdges(bool pressed);
    void changeFacesDiffuseColorRed(double val);
    void changeFacesDiffuseColorGreen(double val);
    void changeFacesDiffuseColorBlue(double val);
    void turnOnOffFaces(bool pressed);

  public:
    DefaultStyleDialog(QWidget *parent, Viewer *viewer);
    virtual ~DefaultStyleDialog(){}
};

/**
 * Button by which is possible to show DefaultStyleDialog
 */
class DefaultStylePushButton : public QPushButton {
    Q_OBJECT

  private:
    QWidget *_parent;
    Viewer *_viewer;

  public:
    DefaultStylePushButton(Viewer *viewer, const QString = "");
    ~DefaultStylePushButton(){}

  private slots:
    void showDialogInternal();

  signals:
    void showDialog(QWidget *widg);
};
#endif

