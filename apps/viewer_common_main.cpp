#ifndef _VIEWER_COMMON_MAIN_CPP_
#define _VIEWER_COMMON_MAIN_CPP_
    int c, option_index;
    float f;
    while ((c = getopt_long(argc, argv, "", options, &option_index)) != -1){
        switch (c){
            case HELP:
                usage(argc, argv);
                break;
            case ALL_OFF:
                viewer->setDefaultSwitch(false);
                break;
            case POINTS_OFF:
                viewer->setDefaultPointsSwitch(false);
                break;
            case EDGES_OFF:
                viewer->setDefaultEdgesSwitch(false);
                break;
            case FACES_OFF:
                viewer->setDefaultFacesSwitch(false);
                break;
            case POINT_SIZE:
                if (!parseFloat(optarg, &f))
                    usage(argc, argv, "Error: option \"--point-size\" require"
                                      " float argument");
                viewer->setDefaultPointSize(f);
                break;
            case EDGE_WIDTH:
                if (!parseFloat(optarg, &f))
                    usage(argc, argv, "Error: option \"--edge-width\" require"
                                      " float argument");
                viewer->setDefaultLineWidth(f);
                break;
            case POINT_COLOR_RED:
                if (!parseFloat(optarg, &f))
                    usage(argc, argv, "Error: option \"--point-color-red\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                viewer->setDefaultPointsDiffuseColorRed(f);
                break;
            case POINT_COLOR_GREEN:
                if (!parseFloat(optarg, &f))
                    usage(argc, argv, "Error: option \"--point-color-green\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                viewer->setDefaultPointsDiffuseColorGreen(f);
                break;
            case POINT_COLOR_BLUE:
                if (!parseFloat(optarg, &f))
                    usage(argc, argv, "Error: option \"--point-color-blue\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                viewer->setDefaultPointsDiffuseColorBlue(f);
                break;
            case EDGE_COLOR_RED:
                if (!parseFloat(optarg, &f))
                    usage(argc, argv, "Error: option \"--edge-color-red\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                viewer->setDefaultEdgesDiffuseColorRed(f);
                break;
            case EDGE_COLOR_GREEN:
                if (!parseFloat(optarg, &f))
                    usage(argc, argv, "Error: option \"--edge-color-green\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                viewer->setDefaultEdgesDiffuseColorGreen(f);
                break;
            case EDGE_COLOR_BLUE:
                if (!parseFloat(optarg, &f))
                    usage(argc, argv, "Error: option \"--edge-color-blue\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                viewer->setDefaultEdgesDiffuseColorBlue(f);
                break;
            case FACE_COLOR_RED:
                if (!parseFloat(optarg, &f))
                    usage(argc, argv, "Error: option \"--face-color-red\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                viewer->setDefaultFacesDiffuseColorRed(f);
                break;
            case FACE_COLOR_GREEN:
                if (!parseFloat(optarg, &f))
                    usage(argc, argv, "Error: option \"--face-color-green\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                viewer->setDefaultFacesDiffuseColorGreen(f);
                break;
            case FACE_COLOR_BLUE:
                if (!parseFloat(optarg, &f))
                    usage(argc, argv, "Error: option \"--face-color-blue\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                viewer->setDefaultFacesDiffuseColorBlue(f);
                break;
            default:
                usage(argc, argv);
        }
    }
#endif
