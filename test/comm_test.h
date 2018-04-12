/*
 * comm_test.h
 * 2018 zhangyule <zyl2336709@gmail.com>
 *
 */

#ifndef CPP_ID_20943_TEST_COMM_TEST_H
#define CPP_ID_20943_TEST_COMM_TEST_H

#include "parsers.h"

struct MyTestStruct {
    int a;
    int b;
    float c;
};

// a:b:c
template <>
struct Parser<MyTestStruct> {
    static bool apply(const std::string& str, MyTestStruct* t) {
        int ret = sscanf(str.c_str(), "%d:%d:%f", &t->a, &t->b, &t->c);
        return ret == 3;
    }
};

#endif /* !COMM_TEST_H */
