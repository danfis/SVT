/**
 * SVT
 * ----------
 * Copyright (c)2007,2008 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of SVT
 *
 * SVT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SVT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SVT. If not, see <http://www.gnu.org/licenses/>.
 */

#include "parser.h"
#include "utils.h"

#define DBG(format, ...) \
    fprintf(stderr, "%s: " format "\n", __func__, __VA_ARGS__); \
    fflush(stderr)
#define DBG2(str) \
    fprintf(stderr, "%s: " str "\n", __func__); \
    fflush(stderr)

svt_parser_t *svtParserNew()
{
    svt_parser_t *parser = ALLOC(svt_parser_t);

    parser->input = stdin;
    parser->objs_head = NULL;
    parser->objs_tail = NULL;
    parser->objs_len = 0;

    parser->cur_tok = -1;
    parser->cur_obj = NULL;

    return parser;
}

void svtParserDelete(svt_parser_t *parser)
{
    svtParserClear(parser);
    free(parser);
}

void svtParserClear(svt_parser_t *parser)
{
    while (parser->objs_head != NULL)
        parser->objs_head = svtObjDelete(parser->objs_head);
}

void svtParserSetInput(svt_parser_t *parser, FILE *input)
{
    parser->input = input;
}

svt_obj_t *svtParserObjs(svt_parser_t *parser, int *len)
{
    if (len != NULL)
        *len = parser->objs_len;
    return parser->objs_head;
}

svt_obj_t *svtParserObjsSteal(svt_parser_t *parser, int *len)
{
    svt_obj_t *objs;

    if (len != NULL)
        *len = parser->objs_len;
    objs = parser->objs_head;

    parser->objs_head = parser->objs_tail = NULL;
    parser->objs_len = 0;

    return objs;
}

/*** PARSE ***/
#define SKIP_DELIMS \
    for (parser->cur_tok = yylex(parser->scanner); \
            parser->cur_tok != 0 \
         && parser->cur_tok != T_ERROR \
         && parser->cur_tok == T_DELIM; \
         parser->cur_tok = yylex(parser->scanner))

#define NEXT parser->cur_tok = yylex(parser->scanner)

static int svtParserParseInit(svt_parser_t *parser);
static void svtParserParseClean(svt_parser_t *parser);

static void svtParserParseObj(svt_parser_t *parser);

static void svtParserParsePoints(svt_parser_t *parser);
static void svtParserParsePoints2d(svt_parser_t *parser);
static void svtParserParseEdges(svt_parser_t *parser);
static void svtParserParseFaces(svt_parser_t *parser);
static void svtParserParseName(svt_parser_t *parser);
static void svtParserParsePoly(svt_parser_t *parser);
static void svtParserParsePolyline(svt_parser_t *parser);
static void svtParserParsePointColor(svt_parser_t *parser);
static void svtParserParseEdgetColor(svt_parser_t *parser);
static void svtParserParseFaceColor(svt_parser_t *parser);
static void svtParserParseError(svt_parser_t *parser);

int svtParserParse(svt_parser_t *parser)
{
    int ret;

    ret = svtParserParseInit(parser);
    if (ret != 0)
        return ret;

    do {
        parser->cur_obj = NULL;

        svtParserParseObj(parser);

        if (parser->cur_obj != NULL){
            // there was parsed some object (by svtParserParseObj()) -> push
            // it to list
            svtObjPush(parser->cur_obj,
                       &parser->objs_head, &parser->objs_tail);
            parser->objs_len++;
        }
    } while (parser->cur_obj != NULL && parser->cur_tok != 0);

    svtParserParseClean(parser);

    return 0;
}

int svtParserParseBegin(svt_parser_t *parser)
{
    return svtParserParseInit(parser);
}

void svtParserParseEnd(svt_parser_t *parser)
{
    svtParserParseClean(parser);
}


int svtParserParseHunk(svt_parser_t *parser, int num_objs)
{
    int parsed = 0;

    do {
        parser->cur_obj = NULL;

        svtParserParseObj(parser);

        if (parser->cur_obj != NULL){
            // there was parsed some object (by svtParserParseObj()) -> push
            // it to list
            svtObjPush(parser->cur_obj,
                       &parser->objs_head, &parser->objs_tail);
            parser->objs_len++;
            parsed++;
        }
    } while (parser->cur_obj != NULL
             && parser->cur_tok != 0
             && parsed < num_objs);

    return parsed;
}


static int svtParserParseInit(svt_parser_t *parser)
{
    if (yylex_init_extra(&parser->yylval, &parser->scanner) != 0){
        perror("Can't initialize scanner");
        return -1;
    }
    yyset_in(parser->input, parser->scanner);

    parser->cur_tok = -1;
    parser->cur_obj = NULL;

    return 0;
}

static void svtParserParseClean(svt_parser_t *parser)
{
    yylex_destroy(parser->scanner);
}

static void svtParserParseObj(svt_parser_t *parser)
{
    char end = 0;

    if (parser->cur_tok == -1 || parser->cur_tok == T_DELIM){
        SKIP_DELIMS;
    }

    while (parser->cur_tok != 0 && !end){
        switch (parser->cur_tok){
            case T_FLT_NUM:
                // if first token is float number it's assumed that
                // this section is points2d
                svtParserParsePoints2d(parser);
                break;
            case T_POINTS:
                svtParserParsePoints(parser);
                break;
            case T_POINTS2D:
                svtParserParsePoints2d(parser);
                break;
            case T_EDGES:
                svtParserParseEdges(parser);
                break;
            case T_FACES:
                svtParserParseFaces(parser);
                break;
            case T_NAME:
                svtParserParseName(parser);
                break;
            case T_POLY:
                svtParserParsePoly(parser);
                break;
            case T_POLYLINE:
                svtParserParsePolyline(parser);
                break;
            case T_POINT_COLOR:
                svtParserParsePointColor(parser);
                break;
            case T_EDGE_COLOR:
                svtParserParseEdgetColor(parser);
                break;
            case T_FACE_COLOR:
                svtParserParseFaceColor(parser);
                break;
            case T_ERROR:
                svtParserParseError(parser);
                break;
            case T_DELIM:
                end = 1;
                break;
            default:
                fprintf(stderr, "Uknown token: %d\n", parser->cur_tok);
                NEXT;
        }
    }
}

static void svtParserParsePoints(svt_parser_t *parser)
{
    float coords[3];
    int i = 0;

    NEXT;
    while (parser->cur_tok == T_FLT_NUM){
        coords[i] = parser->yylval.flt_num;
        i = (i + 1) % 3;

        // three coords already read
        if (i == 0){
            if (parser->cur_obj == NULL)
                parser->cur_obj = svtObjNew();

            svtObjAddPoint(parser->cur_obj,
                           coords[0], coords[1], coords[2]);
        }

        NEXT;
    }

    if (i != 0){
        fprintf(stderr, "In section Points unparsed numbers on line %d: ",
                parser->yylval.lineno);
        if (i == 1)
            fprintf(stderr, "%f", coords[0]);
        if (i == 2)
            fprintf(stderr, "%f %f", coords[0], coords[1]);
        fprintf(stderr, "\n");
    }
}

static void svtParserParsePoints2d(svt_parser_t *parser)
{
    float coords[2];
    int i = 0;

    if (parser->cur_tok == T_POINTS2D){
        NEXT;
    }

    while (parser->cur_tok == T_FLT_NUM){
        coords[i] = parser->yylval.flt_num;
        i = (i + 1) % 2;

        // three coords already read
        if (i == 0){
            if (parser->cur_obj == NULL)
                parser->cur_obj = svtObjNew();

            svtObjAddPoint(parser->cur_obj,
                           coords[0], coords[1], 0.);
        }

        NEXT;
    }

    if (i != 0){
        fprintf(stderr, "In section Points2d unparsed numbers on line %d: ",
                parser->yylval.lineno);
        if (i == 1)
            fprintf(stderr, "%f", coords[0]);
        fprintf(stderr, "\n");
    }
}

static void svtParserParseEdges(svt_parser_t *parser)
{
    int nums[2];
    int i = 0;

    NEXT;
    while (parser->cur_tok == T_INT_NUM){
        nums[i] = parser->yylval.int_num;
        i = (i + 1) % 2;

        if (i == 0){
            if (parser->cur_obj == NULL)
                parser->cur_obj = svtObjNew();

            svtObjAddEdge(parser->cur_obj, nums[0], nums[1]);
        }

        NEXT;
    }

    if (i != 0){
        fprintf(stderr, "In section Edges unparsed numbers on line %d: %d\n",
                parser->yylval.lineno, nums[0]);
    }
}

static void svtParserParseFaces(svt_parser_t *parser)
{
    int nums[3];
    int i = 0;

    NEXT;
    while (parser->cur_tok == T_INT_NUM){
        nums[i] = parser->yylval.int_num;
        i = (i + 1) % 3;

        if (i == 0){
            if (parser->cur_obj == NULL)
                parser->cur_obj = svtObjNew();

            svtObjAddFace(parser->cur_obj, nums[0], nums[1], nums[2]);
        }

        NEXT;
    }

    if (i != 0){
        fprintf(stderr, "In section Faces unparsed numbers on line %d: ",
                parser->yylval.lineno);
        if (i == 1)
            fprintf(stderr, "%d", nums[0]);
        if (i == 2)
            fprintf(stderr, "%d %d", nums[0], nums[1]);
        fprintf(stderr, "\n");
    }
}

static void svtParserParseName(svt_parser_t *parser)
{
    if (strlen(parser->yylval.buffer) > 0){
        if (parser->cur_obj == NULL)
            parser->cur_obj = svtObjNew();

        svtObjSetName(parser->cur_obj, parser->yylval.buffer);
    }

    NEXT;
}

static void svtParserParsePoly(svt_parser_t *parser)
{
    float coords[2];
    int edge = -1, pos, start = -1;
    int i = 0;

    NEXT;
    while (parser->cur_tok == T_FLT_NUM){
        coords[i] = parser->yylval.flt_num;
        i = (i + 1) % 2;

        // three coords already read
        if (i == 0){
            if (parser->cur_obj == NULL)
                parser->cur_obj = svtObjNew();

            pos = svtObjAddPoint(parser->cur_obj,
                                 coords[0], coords[1], 0.);
            if (start == -1)
                start = pos;

            if (edge == -1){
                edge = pos;
            }else{
                svtObjAddEdge(parser->cur_obj, edge, pos);
                edge = pos;
            }
        }

        NEXT;
    }

    if (start != edge)
        svtObjAddEdge(parser->cur_obj, edge, start);

    if (i != 0){
        fprintf(stderr, "In section Poly unparsed numbers on line %d: ",
                parser->yylval.lineno);
        if (i == 1)
            fprintf(stderr, "%f", coords[0]);
        fprintf(stderr, "\n");
    }
}

static void svtParserParsePolyline(svt_parser_t *parser)
{
    float coords[2];
    int edge = -1, pos;
    int i = 0;

    NEXT;
    while (parser->cur_tok == T_FLT_NUM){
        coords[i] = parser->yylval.flt_num;
        i = (i + 1) % 2;

        // three coords already read
        if (i == 0){
            if (parser->cur_obj == NULL)
                parser->cur_obj = svtObjNew();

            pos = svtObjAddPoint(parser->cur_obj,
                                 coords[0], coords[1], 0.);
            if (edge == -1){
                edge = pos;
            }else{
                svtObjAddEdge(parser->cur_obj, edge, pos);
                edge = pos;
            }
        }

        NEXT;
    }

    if (i != 0){
        fprintf(stderr, "In section Polyline unparsed numbers on line %d: ",
                parser->yylval.lineno);
        if (i == 1)
            fprintf(stderr, "%f", coords[0]);
        fprintf(stderr, "\n");
    }
}

static int svtParserParseColor(svt_parser_t *parser, float *nums)
{
    int i = 0;
    float trash;

    NEXT;
    while (parser->cur_tok == T_FLT_NUM && i < 3){
        nums[i] = parser->yylval.flt_num;
        i++;

        if (i == 0){
            if (parser->cur_obj == NULL)
                parser->cur_obj = svtObjNew();

            svtObjAddFace(parser->cur_obj, nums[0], nums[1], nums[2]);
        }

        NEXT;
    }
    
    while (parser->cur_tok == T_FLT_NUM){
        trash = parser->yylval.flt_num;
        fprintf(stderr, "In color section unparsed number %f on line %d\n",
                trash, parser->yylval.lineno);
        NEXT;
    }

    return i;
}
static void svtParserParsePointColor(svt_parser_t *parser)
{
    float nums[3];
    int num;

    num = svtParserParseColor(parser, nums);

    if (num == 3){
        if (parser->cur_obj == NULL)
            parser->cur_obj = svtObjNew();

        svtObjSetPointColor(parser->cur_obj, nums[0], nums[1], nums[2]);
    }
}

static void svtParserParseEdgetColor(svt_parser_t *parser)
{
    float nums[3];
    int num;

    num = svtParserParseColor(parser, nums);

    if (num == 3){
        if (parser->cur_obj == NULL)
            parser->cur_obj = svtObjNew();

        svtObjSetEdgeColor(parser->cur_obj, nums[0], nums[1], nums[2]);
    }
}

static void svtParserParseFaceColor(svt_parser_t *parser)
{
    float nums[3];
    int num;

    num = svtParserParseColor(parser, nums);

    if (num == 3){
        if (parser->cur_obj == NULL)
            parser->cur_obj = svtObjNew();

        svtObjSetFaceColor(parser->cur_obj, nums[0], nums[1], nums[2]);
    }
}

static void svtParserParseError(svt_parser_t *parser)
{
    char buffer[100];
    int i = 1;

    fprintf(stderr, "Unexpected input on line %d: '",
                parser->yylval.lineno);

    buffer[0] = parser->yylval.c;
    while ((NEXT) == T_ERROR){
        buffer[i++] = parser->yylval.c;

        if (i > 99){
            buffer[99] = 0;
            fprintf(stderr, "%s", buffer);
            i = 0;
        }
    }
    buffer[i] = 0;

    if (i != 0){
        fprintf(stderr, "%s", buffer);
    }
    fprintf(stderr, "'\n");
    fflush(stderr);
}

/*** PARSE END ***/
