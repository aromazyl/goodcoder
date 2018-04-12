/*
 * logic.h
 * Copyright (C) 2018 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef LOGIC_H
#define LOGIC_H

#define GTR(...) typename __VA_ARGS__::R

template <int N>
struct Num {
  enum { value = N };
};

struct True : Num<true> {};

struct False : Num<false> {};

template <typename T>
struct CompileAssert;

template <>
struct CompileAssert<True> {};

template <typename Cond, typename If, typename Else>
struct IfThenElse;

template <typename If, typename Else>
struct IfThenElse<True, If, Else> {
  typedef If R;
};

template <typename If, typename Else>
struct IfThenElse<False, If, Else> {
  typedef Else R;
};

template <typename A, typename B>
struct IsSameType {
  typedef False R;
};

template <typename T>
struct IsSameType<T, T> {
  typedef True R;
};

struct NullType {
};

template <typename T, typename L>
struct TypeList {
  typedef T Head;
  typedef L Tail;
};

template <template <typename T> class Func, typename ObjectList>
struct Map;

template <template <typename T> class Func>
struct Map<Func, NullType> {
  typedef NullType R;
};

template <template <typename T> class Func, typename Head, typename Tail>
struct Map<Func, TypeList<Head, Tail>> {
  typedef TypeList<typename Func<Head>::R,
          typename Map<Func, Tail>::R> R;
};

template <template <typename A, typename B> class Func, typename T, typename TList>
struct Foldr;

template <template <typename A, typename B> class Func, typename T>
struct Foldr<Func, T, NullType> {
  typedef T R;
};

template <template <typename A, typename B> class Func, typename T, typename Head, typename Tail>
struct Foldr<Func, T, TypeList<Head, Tail>> {
  typedef GTR(Func<Head, GTR(Foldr<Func, T, Tail>)>) R;
};

template <template <typename A, typename B> class Func, typename T, typename TList>
struct Foldl;

template <template <typename A, typename B> class Func, typename T>
struct Foldl<Func, T, NullType> {
  typedef T R;
};

template <template <typename A, typename B> class Func, typename T, typename Head, typename Tail>
struct Foldl<Func, T, TypeList<Head, Tail>> {
  typedef GTR(Foldl<Func, GTR(Func<T, Head>), Tail>) R;
};

template <typename T>
struct Identity {
  typedef T R;
};

template <typename A, typename B>
struct Pair {
  typedef A A_type;
  typedef B B_type;
  A a;
  B b;
};

template <typename T, int index>
struct GetFromList;

template <typename Head, typename Tail>
struct GetFromList<TypeList<Head, Tail>, 0> {
  typedef Head R;
};

template <int index>
struct GetFromList<NullType, index> {
  typedef NullType R;
};

template <typename Head, typename Tail, int index>
struct GetFromList<TypeList<Head, Tail>, index> {
  typedef GTR(GetFromList<Tail, index - 1>) R;
};

template <typename TL>
struct GetListLen;

template <>
struct GetListLen<NullType> {
  enum { len = 0 };
};

template <typename Head, typename Tail>
struct GetListLen<TypeList<Head, Tail>> {
  enum { len = 1 + GetListLen<Tail>::len };
};

#endif /* !LOGIC_H */
