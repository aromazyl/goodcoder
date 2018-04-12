/*
 * logic_test.cc
 * Copyright (C) 2018 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "trait.h"


// CompileAssert<typename IfThenElse<True,True,False>::R>();
// CompileAssert<typename IfThenElse<False,False,True>::R>();

template <typename T>
struct Func {
    typedef True R;
};

template <typename N1, typename N2>
struct Plus {
    typedef Num<N1::value + N2::value> R;
};

int trait_test() {
    CompileAssert<True>();
    CompileAssert<GTR(IfThenElse<True, True, False>)>();
    CompileAssert<GTR(IfThenElse<False, False, True>)>();
    CompileAssert<GTR(IsSameType<True, True>)>();
    CompileAssert<GTR(IsSameType<NullType, NullType>)>();
    CompileAssert<GTR(Map<Func, TypeList<False, NullType>>)::Head>();
    CompileAssert<GTR(IsSameType<GTR(Map<Identity, TypeList<True, TypeList<False, NullType>>>),
            TypeList<True, TypeList<False, NullType>>>)>();
    CompileAssert<GTR(IsSameType<GTR(Foldr<Plus, Num<4>, TypeList<Num<1>, TypeList<Num<2>, NullType>>>), Num<7>>)>();
    CompileAssert<GTR(IsSameType<GTR(Foldl<Plus, Num<4>, TypeList<Num<1>, TypeList<Num<2>, NullType>>>), Num<7>>)>();

    return 0;
}
