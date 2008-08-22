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
};

#endif
