#ifndef SETTINGS_HPP
#define SETTINGS_HPP

struct Settings {
    static bool all_off;
    static bool points_off;
    static bool edges_off;
    static bool faces_off;

    static float point_size;
    static float edge_width;

    static float point_color[3]; /* rgb */
    static float edge_color[3];
    static float face_color[3];

    static bool colour_points;
    static bool colour_edges;
    static bool colour_faces;

#ifdef TO_SVG
    static int svg_width;
    static bool svg_view_box_enabled;
    static float svg_view_box[4];
    static int svg_precision;
    static float svg_bg_color[3];
#endif
};

#endif
