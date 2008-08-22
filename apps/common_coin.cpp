#include "common_coin.hpp"
#include "common.hpp"
#include "settings.hpp"
#include "objdata.hpp"
#include "viewer.hpp"
#include "coin3dtools.hpp"

void parseObjData()
{
    svt_obj_t *objs;
    ObjData *data;
    Viewer *viewer;
    float r, g, b;

    viewer = Coin3dTools::viewer();

    if (svtParserParse(parser) != 0){
        ERR("Can't parse input");
        return;
    }

    objs = svtParserObjsSteal(parser, NULL);
    while (objs != NULL){
        data = new ObjData(objs);
        viewer->addObjData(data);

        // colour elemets if requested
        if (Settings::colour_points){
            chooseRandomColor(&r, &g, &b);
            data->material_points->diffuseColor.setValue(r, g, b);
        }
        if (Settings::colour_edges){
            chooseRandomColor(&r, &g, &b);
            data->material_edges->diffuseColor.setValue(r, g, b);
        }
        if (Settings::colour_faces){
            chooseRandomColor(&r, &g, &b);
            data->material_faces->diffuseColor.setValue(r, g, b);
        }

        objs = svtObjDelete(objs);
    }
}


void applySettings(Viewer *viewer)
{
    viewer->setDefaultSwitch(!Settings::all_off);
    viewer->setDefaultPointsSwitch(!Settings::points_off);
    viewer->setDefaultEdgesSwitch(!Settings::edges_off);
    viewer->setDefaultFacesSwitch(!Settings::faces_off);

    viewer->setDefaultPointSize(Settings::point_size);
    viewer->setDefaultLineWidth(Settings::edge_width);

    viewer->setDefaultPointsDiffuseColorRed(Settings::point_color[0]);
    viewer->setDefaultPointsDiffuseColorGreen(Settings::point_color[1]);
    viewer->setDefaultPointsDiffuseColorBlue(Settings::point_color[2]);
    viewer->setDefaultEdgesDiffuseColorRed(Settings::edge_color[0]);
    viewer->setDefaultEdgesDiffuseColorGreen(Settings::edge_color[1]);
    viewer->setDefaultEdgesDiffuseColorBlue(Settings::edge_color[2]);
    viewer->setDefaultFacesDiffuseColorRed(Settings::face_color[0]);
    viewer->setDefaultFacesDiffuseColorGreen(Settings::face_color[1]);
    viewer->setDefaultFacesDiffuseColorBlue(Settings::face_color[2]);
}
