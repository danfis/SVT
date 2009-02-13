#include "faces.hpp"



SVT::Qt2D::Faces::Faces(svt_obj_t *obj)
    : _num_faces(0)
{
    const svt_face_t *faces;
    int faces_len;
    const svt_point_t *points;
    int points_len;
    int id1, id2, id3;
    const float *color;

    // save faces to path
    points = svtObjPoints(obj, &points_len);
    faces = svtObjFaces(obj, &faces_len);
    for (int i=0; i < faces_len; i++){
        id1 = faces[i][0];
        id2 = faces[i][1];
        id3 = faces[i][2];
        _path.moveTo(points[id1][0], points[id1][1]);
        _path.lineTo(points[id2][0], points[id2][1]);
        _path.lineTo(points[id3][0], points[id3][1]);
        _path.lineTo(points[id1][0], points[id1][1]);
    }
    _num_faces = faces_len;

    // get color
    color = svtObjEdgeColor(obj);
    if (color != NULL)
        setColor(color[0], color[1], color[2]);

    // get size
    setSize(1.);
}

SVT::Qt2D::Faces::~Faces()
{
}

void SVT::Qt2D::Faces::paint(QPainter &painter)
{
    if (!on())
        return;

    painter.setPen(pen());
    painter.drawPath(_path);
}
