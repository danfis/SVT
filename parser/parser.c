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
    parser->objs = NULL;
    parser->objs_len = 0;

    parser->cur_tok = -1;
    parser->cur_obj = NULL;

    return parser;
}

void svtParserDelete(svt_parser_t *parser)
{
    while (parser->objs != NULL)
        parser->objs = svtObjDelete(parser->objs);
    free(parser);
}

void svtParserSetInput(svt_parser_t *parser, FILE *input)
{
    parser->input = input;
}

svt_obj_t *svtParserObjs(svt_parser_t *parser, int *len)
{
    if (len != NULL)
        *len = parser->objs_len;
    return parser->objs;
}

svt_obj_t *svtParserObjsSteal(svt_parser_t *parser, int *len)
{
    svt_obj_t *objs;

    if (len != NULL)
        *len = parser->objs_len;
    objs = parser->objs;

    parser->objs = NULL;
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

static void svtParserParseObj(svt_parser_t *parser);

static void svtParserParsePoints(svt_parser_t *parser);
static void svtParserParsePoints2d(svt_parser_t *parser);
static void svtParserParseEdges(svt_parser_t *parser);
static void svtParserParseFaces(svt_parser_t *parser);
static void svtParserParseName(svt_parser_t *parser);
static void svtParserParseError(svt_parser_t *parser);

int svtParserParse(svt_parser_t *parser)
{
    if (yylex_init_extra(&parser->yylval, &parser->scanner) != 0){
        perror("Can't initialize scanner");
        return -1;
    }
    yyset_in(parser->input, parser->scanner);

    if (parser->cur_tok == -1 || parser->cur_tok == T_DELIM){
        SKIP_DELIMS;
    }

    do {
        parser->cur_obj = NULL;

        svtParserParseObj(parser);

        if (parser->cur_obj != NULL){
            // there was parsed some object (by svtParserParseObj()) -> push
            // it to list
            svtObjPush(parser->cur_obj, parser->objs);
            parser->objs = parser->cur_obj;
            parser->objs_len++;
        }
    } while (parser->cur_obj != NULL && parser->cur_tok != 0);

    yylex_destroy(parser->scanner);

    return 0;
}

static void svtParserParseObj(svt_parser_t *parser)
{
    char end = 0;

    if (parser->cur_tok == -1 || parser->cur_tok == T_DELIM){
        SKIP_DELIMS;
    }

    while (parser->cur_tok != 0 && !end){
        switch (parser->cur_tok){
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
    double coords[3];
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

    NEXT;
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
            buffer[i] = 0;
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
