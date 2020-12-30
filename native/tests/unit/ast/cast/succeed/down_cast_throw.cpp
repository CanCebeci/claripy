/** @file */

#include "ast/base.hpp"
#include "ast/cast.hpp"
#include "ast/int.hpp"
#include "testlib.hpp"

#include <set>


// For brevity
using namespace AST;
using namespace UnitTest::TestLib;


/* Down casting should succeed */
int down_cast_throw() {
    Int a = construct_ast<Int>();
    Base b = up_cast<Base>(a);
    Int c = down_cast_throw_on_fail<Int>(a);
    UNITTEST_ASSERT(c == a)
    return 0;
}