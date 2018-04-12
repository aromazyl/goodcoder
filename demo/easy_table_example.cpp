/*
 * easy_table_example.cpp
 * Copyright (C) 2018 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include "table.h"

struct TestStructA {
};

struct TestStructB {
    int a;
    float b;
    char c[100];
};

bool parse_test_struct_a(const std::string& s, TestStructA* r) {
    return true;
}

bool parse_test_struct_b(const std::string& s, TestStructB* r) {
    if (s.empty()) {
        return false;
    }
    int ret = sscanf(s.c_str(), "%d-%f-%s", &r->a, &r->b, &r->c);
    return ret == 3;
}

RS_STRUCT(TestStructA, parse_test_struct_a);
RS_STRUCT(TestStructB, parse_test_struct_b);

typedef ST_TABLE(int, VEC(TestStructA), VEC(TestStructB), char*) MyTABLE;
typedef typename MyTABLE::FieldPairs INS;

int main() {
    TestStructB r;
    MyTABLE table;
    char buf[2048] = {0};
    while (fgets(buf, sizeof(char) * 2048, stdin)) {
        if (table.parse_line(buf)) {
            INS* ins = table.get_current_instance();
            auto b = table.seek<2>(ins);
            printf("%d, a, ", *table.seek<0>(ins));
            for (auto& bp : *b) {
                printf("\t%d-%f-%s", bp.a, bp.b, bp.c);
            }
            printf("\t%s\n", *table.seek<3>(ins));
        }
        memset(buf, 0, sizeof(char) * 2048);
    }
    return 0;
}
