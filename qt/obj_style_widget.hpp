#ifndef QT_OBJ_STYLE_WIDGET_HPP
#define QT_OBJ_STYLE_WIDGET_HPP

#include <QDoubleSpinBox>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

namespace Qt {

enum ObjStyleWidgetFlags {
    OBJ_STYLE_WIDGET_POINTS = 0x1,
    OBJ_STYLE_WIDGET_EDGES = 0x2,
    OBJ_STYLE_WIDGET_FACES = 0x4,
    OBJ_STYLE_WIDGET_ALL = 0x7
};

class ObjStyleWidget : public QWidget {
    Q_OBJECT

  private:
    void *_obj;
    int _flags;

    QDoubleSpinBox *_points[4]; /* size, r, g, b */
    QPushButton *_points_b;
    QDoubleSpinBox *_edges[4];
    QPushButton *_edges_b;
    QDoubleSpinBox *_faces[3]; /* r, g, b */
    QPushButton *_faces_b;

    QWidget *_buildPoints();
    QWidget *_buildEdges();
    QWidget *_buildFaces();

    void _buildColors(QVBoxLayout *layout, QDoubleSpinBox **refs);
    void _buildSize(QVBoxLayout *layout, QDoubleSpinBox **refs);
    void _buildOnOff(QVBoxLayout *layout, QPushButton **refs);

    void _setUpConnections();

  public:
    ObjStyleWidget(void *obj, int flags = OBJ_STYLE_WIDGET_ALL);

  public slots:
    void setPointSize(double val);
    void setPointColor(double val[3]);
    void setPointColor(double r, double g, double b);
    void setPointColorRed(double val);
    void setPointColorGreen(double val);
    void setPointColorBlue(double val);
    void setPointOnOff(bool on);

    void setEdgeWidth(double val);
    void setEdgeColor(double val[3]);
    void setEdgeColor(double r, double g, double b);
    void setEdgeColorRed(double val);
    void setEdgeColorGreen(double val);
    void setEdgeColorBlue(double val);
    void setEdgeOnOff(bool on);

    void setFaceColor(double val[3]);
    void setFaceColor(double r, double g, double b);
    void setFaceColorRed(double val);
    void setFaceColorGreen(double val);
    void setFaceColorBlue(double val);
    void setFaceOnOff(bool on);


  private slots:
    void _pointSize(double val);
    void _pointColorRed(double val);
    void _pointColorBlue(double val);
    void _pointColorGreen(double val);
    void _pointOnOff(bool off);

    void _edgeWidth(double val);
    void _edgeColorRed(double val);
    void _edgeColorBlue(double val);
    void _edgeColorGreen(double val);
    void _edgeOnOff(bool off);

    void _faceColorRed(double val);
    void _faceColorBlue(double val);
    void _faceColorGreen(double val);
    void _faceOnOff(bool off);

  signals:
    void pointSize(void *obj, double val);
    void pointColorRed(void *obj, double val);
    void pointColorBlue(void *obj, double val);
    void pointColorGreen(void *obj, double val);
    void pointColor(void *obj, double r, double g, double b);
    void pointOnOff(void *obj, bool on);

    void edgeWidth(void *obj, double val);
    void edgeColorRed(void *obj, double val);
    void edgeColorBlue(void *obj, double val);
    void edgeColorGreen(void *obj, double val);
    void edgeColor(void *obj, double r, double g, double b);
    void edgeOnOff(void *obj, bool on);

    void faceColorRed(void *obj, double val);
    void faceColorBlue(void *obj, double val);
    void faceColorGreen(void *obj, double val);
    void faceColor(void *obj, double r, double g, double b);
    void faceOnOff(void *obj, bool on);
};

};
#endif
