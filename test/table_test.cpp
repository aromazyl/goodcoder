/*
 * table_test.cpp
 * Copyright (C) 2018 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <vector>
#include <string>
#include <gtest/gtest.h>
#include <iostream>
#include <string.h>
#include "comm_test.h"
#include "type_ops.h"
#include "table.h"

class TableTest : public ::testing::Test {
    public:
        void SetUp() {}
        void TearDown() {}

        typedef
            ST_TABLE(int, float, char*, VEC(MyTestStruct))
            TEST_TABLE;

        typedef typename TEST_TABLE::FieldPairs INS;

        TEST_TABLE table;

};

TEST_F(TableTest, Table) {
    EXPECT_FALSE(table.parse_line(""));
    EXPECT_TRUE(table.parse_line("2\t3.1\tabc\t1:2:2:3.0"));
    EXPECT_TRUE(table.parse_line("4\t6.2\tedf\t1:7:2:3.0"));
    EXPECT_TRUE(table.parse_line("1\t2.1\tfga\t2:2:2:3.0,7:2:222.1"));

    EXPECT_EQ(3, table.size());

    INS* ins = table.get_current_instance();
    auto ret = table.seek<0>(ins);
    EXPECT_EQ(*ret, 1);
    EXPECT_EQ(*table.seek<1>(ins), 2.1f);
    auto res = (strcmp(*table.seek<2>(ins), "fga") == 0);
    EXPECT_TRUE(res);
    auto* vec = table.seek<3>(ins);
    EXPECT_EQ(vec->size(), 2);
    EXPECT_EQ(vec->at(0).a, 2);
    EXPECT_EQ(vec->at(1).c, 222.1f);
    EXPECT_EQ(ins, table.get_instance_by_index(2));
}
