/*
 * type_ops_test.cpp
 * Copyright (C) 2018 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <vector>
#include <string>
#include <gtest/gtest.h>
#include <iostream>
#include "comm_test.h"
#include "type_ops.h"

class TypeOpsTest : public ::testing::Test {
    public:
        void SetUp() {}
        void TearDown() {}
};

TEST_F(TypeOpsTest, MakePairTest) {
    CompileAssert<GTR(IsSameType<GTR(MakePairs<int, int, bool, float>),
            Pair<int, Pair<int, Pair<bool, Pair<float, NullType>>>>>)>();
    CompileAssert<GTR(IsSameType<GTR(MakeLists<int, int, bool, float>),
            TypeList<int, TypeList<int, TypeList<bool, TypeList<float, NullType>>>>>)>();
}

TEST_F(TypeOpsTest, ParseTest) {
    using TestPairs = GTR(MakePairs<int, float, VEC(MyTestStruct)>);
    using TestLists = GTR(MakeLists<int, float, VEC(MyTestStruct)>);

    TestPairs pairs;
    EXPECT_EQ(GetListLen<TestLists>::len, 3);

    std::vector<std::string> terms = {"1", "2.0", "2:2:4:3.0,2:7:5.5"};
    bool ret = Parse<TestLists,TestPairs,0,GetListLen<TestLists>::len>::parse(terms, pairs);
    EXPECT_TRUE(ret);
    EXPECT_EQ(pairs.a, 1);
    EXPECT_EQ(pairs.b.a, 2.0f);
    EXPECT_EQ(pairs.b.b.a.at(0).a, 2);
    EXPECT_EQ(pairs.b.b.a.at(0).b, 4);
    EXPECT_EQ(pairs.b.b.a.at(0).c, 3.0f);
    EXPECT_EQ(pairs.b.b.a.at(1).a, 2);
    EXPECT_EQ(pairs.b.b.a.at(1).b, 7);
    EXPECT_EQ(pairs.b.b.a.at(1).c, 5.5f);
    terms[0] = "a";
    ret = Parse<TestLists, TestPairs, 0, GetListLen<TestLists>::len>::parse(terms, pairs);
    EXPECT_FALSE(ret);
}
