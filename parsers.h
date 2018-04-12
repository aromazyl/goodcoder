/*
 * parsers.h
 * Copyright (C) 2018 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef CPP_ID_20943_PARSERS_H
#define CPP_ID_20943_PARSERS_H

#include <vector>
#include <stdio.h>
#include <string.h>
#include <string>
#include <inttypes.h>
#include <stdlib.h>
#include <algorithm>
#include "trait.h"

template <typename T>
struct Parser;

template <>
struct Parser<int> {
    static bool apply(const std::string& str, int* n) {
        if (!n || str.empty()) {
            return false;
        }

        char *end = NULL;
        char s[20] = {0};
        memcpy(s, str.c_str(), std::min((size_t)19, str.size()) * sizeof(char));

        char * endptr;
        *n = strtol(s, &endptr, 0);
        return (*endptr == '\0');
    }
};

template <>
struct Parser<char*> {
    static bool apply(const std::string& str, char** mem) {
        if (mem == NULL) {
            return false;
        }
        *mem = (char*)malloc(sizeof(char) * (str.size() + 1));
        memset(*mem, 0, sizeof(char) * (str.size() + 1));
        memcpy((void*)(*mem), str.c_str(), sizeof(char) * str.size());
        return true;
    }
};

template <>
struct Parser<float> {
    static bool apply(const std::string& str, float* n) {
        if (str.empty() || !n) {
            return false;
        }
        char * endptr;
        *n = strtof(str.c_str(), &endptr);

        return *endptr == '\0';
    }
};

template <>
struct Parser<NullType> {
    static bool apply(const std::string&, NullType*) {
        return true;
    }
};

template <typename T>
struct Parser<std::vector<T>> {
    static bool apply(const std::string& str, std::vector<T>* n) {
        if (n == NULL || str.empty()) {
            return false;
        }
        n->clear();
        int st = 0;
        int vec_size = 0;
        int turn_off = false;
        T t;
        for (int i = 0; i < str.size(); ++i) {
            if (str[i] == ':' && !turn_off) {
                bool ret = Parser<int>::apply(str.substr(0, i), &vec_size);
                if (!ret) {
                    fprintf(stderr, "%s, %d, parse error, str[%s]\n",
                            __FILE__, __LINE__, str.substr(0, i).c_str());
                    return false;
                }
                n->reserve(vec_size);
                st = i + 1;
                turn_off = true;
            }
            if (str[i] == ',') {
                bool ret = Parser<T>::apply(str.substr(st, i-st), &t);
                if (!ret) {
                    fprintf(stderr, "%s, %d, parse error, str[%s]\n",
                            __FILE__, __LINE__, str.substr(st, i-st).c_str());
                    return false;
                }
                st = i + 1;
                n->push_back(t);
            }
        }

        if (vec_size != n->size() + 1) {
            fprintf(stderr, "%s, %d, vec_size not match, str[%s]\n",
                    __FILE__, __LINE__, str.substr(st).c_str());
            n->clear();
            return false;
        }

        if (vec_size != 0) {
            bool ret = Parser<T>::apply(str.substr(st), &t);
            if (!ret) {
                fprintf(stderr, "%s, %d, parse error, str[%s]\n",
                        __FILE__, __LINE__, str.substr(st).c_str());
                return false;
            }
            n->push_back(t);
        }

        return true;
    }
};

#define VEC(...) std::vector<__VA_ARGS__>

#define RS_STRUCT(name, parse_method) \
    template <> \
struct Parser<name> { \
    static bool apply(const std::string& s, name* r) { \
        return parse_method(s, r); \
    }; \
}; \

#endif /* !PARSERS_H */
