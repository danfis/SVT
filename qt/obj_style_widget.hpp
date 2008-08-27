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
    ObjStyleWidgetFlags _flags;

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
    ObjStyleWidget(void *obj,
                   ObjStyleWidgetFlags flags = OBJ_STYLE_WIDGET_ALL);

  public slots:
    void setPointSize(float val);
    void setPointColor(float val[3]);
    void setPointColor(float r, float g, float b);
    void setPointColorRed(float val);
    void setPointColorGreen(float val);
    void setPointColorBlue(float val);
    void setPointOnOff(bool on);

    void setEdgeWidth(float val);
    void setEdgeColor(float val[3]);
    void setEdgeColor(float r, float g, float b);
    void setEdgeColorRed(float val);
    void setEdgeColorGreen(float val);
    void setEdgeColorBlue(float val);
    void setEdgeOnOff(bool on);

    void setFaceColor(float val[3]);
    void setFaceColor(float r, float g, float b);
    void setFaceColorRed(float val);
    void setFaceColorGreen(float val);
    void setFaceColorBlue(float val);
    void setFaceOnOff(bool on);


  private slots:
    void _pointSize(float val);
    void _pointColorRed(float val);
    void _pointColorBlue(float val);
    void _pointColorGreen(float val);
    void _pointColor(float r, float g, float b);
    void _pointOnOff(bool on);

    void _edgeWidth(float val);
    void _edgeColorRed(float val);
    void _edgeColorBlue(float val);
    void _edgeColorGreen(float val);
    void _edgeColor(float r, float g, float b);
    void _edgeOnOff(bool on);

    void _faceColorRed(float val);
    void _faceColorBlue(float val);
    void _faceColorGreen(float val);
    void _faceColor(float r, float g, float b);
    void _faceOnOff(bool on);

  signals:
    void pointSize(void *obj, float val);
    void pointColorRed(void *obj, float val);
    void pointColorBlue(void *obj, float val);
    void pointColorGreen(void *obj, float val);
    void pointColor(void *obj, float r, float g, float b);
    void pointOnOff(void *obj, bool on);

    void edgeWidth(void *obj, float val);
    void edgeColorRed(void *obj, float val);
    void edgeColorBlue(void *obj, float val);
    void edgeColorGreen(void *obj, float val);
    void edgeColor(void *obj, float r, float g, float b);
    void edgeOnOff(void *obj, bool on);

    void faceColorRed(void *obj, float val);
    void faceColorBlue(void *obj, float val);
    void faceColorGreen(void *obj, float val);
    void faceColor(void *obj, float r, float g, float b);
    void faceOnOff(void *obj, bool on);
};

};
#endif
