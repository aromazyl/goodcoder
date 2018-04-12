/*
 * parsers_test.cpp
 * Copyright (C) 2018 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <gtest/gtest.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "comm_test.h"


class ParserTest : public ::testing::Test {
public:
  void SetUp() {}
  void TearDown() {}

private:
};


TEST_F(ParserTest, Parser_int) {
  int ret;
  EXPECT_TRUE(Parser<int>::apply("222", &ret));
  EXPECT_EQ(222, ret);
  EXPECT_TRUE(Parser<int>::apply("-222", &ret));
  EXPECT_EQ(-222, ret);
  EXPECT_FALSE(Parser<int>::apply("-122asdf", &ret));
  EXPECT_FALSE(Parser<int>::apply("", &ret));
  EXPECT_FALSE(Parser<int>::apply("222", NULL));
}

#ifndef FREE
#define FREE(a) \
  do { \
    if (a) { \
      free(a); \
    } \
    a = NULL; \
  } while (0); \

TEST_F(ParserTest, Parser_char_star) {
  char* a = NULL;
  EXPECT_TRUE(Parser<char*>::apply("", &a));
  EXPECT_TRUE(Parser<char*>::apply("123", &a));
  EXPECT_EQ(strlen(a), 3);
  EXPECT_TRUE(strcmp("123", a) == 0);
  FREE(a);
}

#undef FREE
#endif

TEST_F(ParserTest, Parser_float) {
  float a;
  EXPECT_TRUE(Parser<float>::apply("12.3", &a));
  EXPECT_TRUE(fabs(a - 12.3f) < 0.000001);
  EXPECT_FALSE(Parser<float>::apply("", &a));
  EXPECT_FALSE(Parser<float>::apply("1a2", &a));
}

TEST_F(ParserTest, Parser_MyTestStruct) {
  MyTestStruct unit;
  EXPECT_TRUE(Parser<MyTestStruct>::apply("222:111:12.8", &unit));
  EXPECT_EQ(unit.a, 222);
  EXPECT_EQ(unit.b, 111);
  EXPECT_TRUE(fabs(unit.c - 12.8) < 0.000001);
  EXPECT_FALSE(Parser<MyTestStruct>::apply("", &unit));
  EXPECT_FALSE(Parser<MyTestStruct>::apply("lkajkdf", &unit));
  EXPECT_FALSE(Parser<MyTestStruct>::apply("222:111:", &unit));
}

TEST_F(ParserTest, ParserVec) {
  typedef VEC(int) vec_int;
  vec_int res;
  EXPECT_TRUE(Parser<vec_int>::apply("2:1,2", &res));
  EXPECT_EQ(res.size(), 2);
  EXPECT_EQ(res.at(0), 1);
  EXPECT_EQ(res.at(1), 2);
  EXPECT_FALSE(Parser<vec_int>::apply("3:1", &res));
  EXPECT_FALSE(Parser<vec_int>::apply("", &res));
  typedef VEC(MyTestStruct) vec_MyTestStruct;
  vec_MyTestStruct vec;
  EXPECT_TRUE(Parser<vec_MyTestStruct>::apply("2:2:2:3.0,4:4:5.0", &vec));
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec.at(0).a, 2);
  EXPECT_EQ(vec.at(0).b, 2);
  EXPECT_EQ(vec.at(0).c, 3.0f);
  EXPECT_EQ(vec.at(1).a, 4);
  EXPECT_EQ(vec.at(1).b, 4);
  EXPECT_EQ(vec.at(1).c, 5.0f);
  EXPECT_FALSE(Parser<vec_MyTestStruct>::apply("", &vec));
}
