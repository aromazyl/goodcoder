/*
 * type_ops.h
 * Copyright (C) 2018 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef TYPE_OPS_H
#define TYPE_OPS_H

#include <vector>
#include "trait.h"
#include "parsers.h"

template <typename...T>
struct MakePairs;

template <typename T>
struct MakePairs<T> : Pair<T, NullType> {
  typedef Pair<T, NullType> R;
};

template <typename FirstType, typename... RestType>
struct MakePairs<FirstType, RestType...> : Pair<FirstType, GTR(MakePairs<RestType...>)> {
  typedef Pair<FirstType, GTR(MakePairs<RestType...>)> R;
};

template <typename...T>
struct MakeLists;
template <typename T>
struct MakeLists<T> {
  typedef TypeList<T, NullType> R;
};

template <typename FirstType, typename... RestType>
struct MakeLists<FirstType, RestType...> {
  typedef TypeList<FirstType, GTR(MakeLists<RestType...>)> R;
};

template <typename FieldTypes, typename FieldPairs, int index, int N>
struct Parse {
  static_assert(index < N, "index should less than N");
  static_assert(index >= 0, "index should larger than N");
  typedef GTR(GetFromList<FieldTypes, index>) ftype;
  static bool parse(const std::vector<std::string>& terms, FieldPairs& results) {
    return Parser<ftype>::apply(terms[index], &results.a) &&
      Parse<FieldTypes, typename FieldPairs::B_type, index + 1, N>::parse(terms, results.b);
  }
};

template <typename FieldTypes, typename FieldPairs, int N>
struct Parse<FieldTypes, FieldPairs, N, N> {
  static bool parse(const std::vector<std::string>& terms, FieldPairs& results) {
    return true;
  }
};

template <typename PairType, typename T, int i>
struct GetFieldData {
  static T* get(PairType& fpair) {
    return GetFieldData<typename PairType::B_type, T, i-1>::get(fpair.b);
  }
};

template <typename Any, typename T>
struct GetFieldData<Pair<T, Any>, T, 0> {
  static T* get(Pair<T, Any>& pairs) {
    return &pairs.a;
  }
};

#endif /* !TYPE_OPS_H */
