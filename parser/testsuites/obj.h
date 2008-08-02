#ifndef OBJ_H
#define OBJ_H

#include "cu.h"

TEST(ObjSetUp);
TEST(ObjTearDown);

TEST(ObjAddElements);

TEST_SUITE(TSObj){
    TEST_ADD(ObjSetUp),

    TEST_ADD(ObjAddElements),

    TEST_ADD(ObjTearDown),
    TEST_SUITE_CLOSURE
};

#endif
