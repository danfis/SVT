#include "parser.h"
#include "utils.h"

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
                //_parseDelim();
                end = 1;
                break;
            default:
                //cout << "Token: " << _cur_token << endl;
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

    /* TODO
    if (i != 0){
        cerr << "Some numbers unparsed: ";
        if (i == 1)
            cerr << coords[0] << endl;
        if (i == 2)
            cerr << coords[0] << " " << coords[1] << endl;
    }
    */
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

    /* TODO
    if (i != 0){
        cerr << "Some numbers unparsed: ";
        if (i == 1)
            cerr << coords[0] << endl;
    }
    */
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

    /* TODO
    if (i != 0){
        cerr << "Some numbers unparsed: " << nums[0] << endl;
    }
    */
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

    /* TODO
    if (i != 0){
        cerr << "Some numbers unparsed: ";
        if (i == 1)
            cerr << nums[0] << endl;
        if (i == 2)
            cerr << nums[0] << " " << nums[1] << endl;
    }
    */
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
    fprintf(stderr, "\n");
    fflush(stderr);
}

/*** PARSE END ***/
