#ifndef PARSER_H
#define PARSER_H

#include "cu.h"

TEST(ParserSetUp);
TEST(ParserTearDown);

TEST(ParserParse);

TEST(ParserParseHunk);

TEST_SUITE(TSParser) {
    TEST_ADD(ParserSetUp),

    TEST_ADD(ParserParse),
    TEST_ADD(ParserParseHunk),

    TEST_ADD(ParserTearDown),
    TEST_SUITE_CLOSURE
};

#endif
