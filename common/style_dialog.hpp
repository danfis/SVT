#ifndef _STYLE_WINDOW_HPP_
#define _STYLE_WINDOW_HPP_

#include <QDialog>
#include <QPushButton>
#include "objdata.hpp"

class Viewer;

/**
 * Class which provides dialog for configuring of properties(style) of one
 * ObjData object.
 */
class StyleDialog : public QDialog {
    Q_OBJECT

  protected:
    ObjData *_data;
    Viewer *_viewer;

    QWidget *_buildPoints();
    QWidget *_buildEdges();
    QWidget *_buildFaces();

    void lock();
    void unlock();
  protected slots:
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
    StyleDialog(QWidget *parent, Viewer *viewer, ObjData *data);
    virtual ~StyleDialog(){}
};


/**
 * Button by which is possible to show StyleDialog
 */
class StylePushButton : public QPushButton {
    Q_OBJECT

  private:
    QWidget *_parent;
    Viewer *_viewer;
    ObjData *_data;

  public:
    StylePushButton(Viewer *viewer, ObjData *data, const QString = "");
    ~StylePushButton(){}

  private slots:
    void showDialogInternal();

  signals:
    void showDialog(QWidget *widg);
};
#endif
