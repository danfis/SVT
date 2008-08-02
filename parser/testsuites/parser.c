#include "cu.h"
#include "../parser.h"

static svt_parser_t *parser;

TEST(ParserSetUp)
{
    parser = svtParserNew();
}

TEST(ParserTearDown)
{
    svtParserDelete(parser);
}
