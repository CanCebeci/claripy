/**
 * @file
 * \ingroup unittest
 */
#include "binary.hpp"
#include "flat.hpp"
#include "uint_binary.hpp"
#include "unary.hpp"


/** Test the trivial create functions */
void trivial() {
    namespace Log = Util::Log;
    namespace Ex = Expr;
    namespace Cr = Create;

    /********************************************************************/
    /*                              Unary                               */
    /********************************************************************/

    Log::debug("Testing abs...");
    unary<Ex::FP, Op::Abs, Cr::abs>();

    Log::debug("Testing neg...");
    unary<Ex::BV, Op::Neg, Cr::neg>();
    unary<Ex::FP, Op::Neg, Cr::neg>();

    Log::debug("Testing not...");
    unary<Ex::Bool, Op::Not, Cr::not_>();

    Log::debug("Testing invert...");
    unary<Ex::BV, Op::Invert, Cr::invert>();

    Log::debug("Testing reverse...");
    unary<Ex::BV, Op::Reverse, Cr::reverse>();

    /********************************************************************/
    /*                            Int Binary                            */
    /********************************************************************/

    Log::debug("Testing sign_ext...");
    uint_binary<Ex::BV, Op::SignExt, SM::Add, Cr::sign_ext>();

    Log::debug("Testing zero_ext...");
    uint_binary<Ex::BV, Op::ZeroExt, SM::Add, Cr::zero_ext>();

    /********************************************************************/
    /*                              Binary                              */
    /********************************************************************/

    // Comparisons

    Log::debug("Testing eq...");
    binary<Ex::Bool, Ex::FP, Op::Eq, SM::First, Cr::eq<Expr::FP>>();
    binary<Ex::Bool, Ex::BV, Op::Eq, SM::First, Cr::eq<Expr::BV>>();
    binary<Ex::Bool, Ex::Bool, Op::Eq, SM::First, Cr::eq<Expr::Bool>>();
    binary<Ex::Bool, Ex::String, Op::Eq, SM::First, Cr::eq<Expr::String>>();

/** A local macro used to test a comparison function */
#define TEST_COMPARE(T_, MASK)                                                                    \
    binary<Ex::Bool, T_, Op::Compare<MASK>, SM::First, Cr::compare<T_, MASK>>();

/** A local macro used to test a comparison function for all values of Less and Equals */
#define TEST_COMPARE_MULTI(T_, S_)                                                                \
    TEST_COMPARE(T_, S_ | C::Less | C::Eq);                                                       \
    TEST_COMPARE(T_, S_ | C::Less | C::Neq);                                                      \
    TEST_COMPARE(T_, S_ | C::Greater | C::Eq);                                                    \
    TEST_COMPARE(T_, S_ | C::Greater | C::Neq);

    Log::debug("Testing compare...");
    {
        using C = Mode::Compare;
        TEST_COMPARE_MULTI(Ex::FP, C::Signed)   // FP comparisons must be signed
        TEST_COMPARE_MULTI(Ex::BV, C::Unsigned) // BV can be either
        TEST_COMPARE_MULTI(Ex::BV, C::Unsigned)
    }

// Cleanup
#undef TEST_COMPARE
#undef TEST_COMPARE_MULTI

    // Math

    Log::debug("Testing sub...");
    binary<Ex::BV, Op::Sub, SM::First, Cr::sub>();

    Log::debug("Testing div...");
    binary<Ex::BV, Op::Div<true>, SM::First, Cr::div<true>>();
    binary<Ex::BV, Op::Div<false>, SM::First, Cr::div<false>>();

    Log::debug("Testing mod...");
    binary<Ex::BV, Op::Mod<true>, SM::First, Cr::mod<true>>();
    binary<Ex::BV, Op::Mod<false>, SM::First, Cr::mod<false>>();

    // Bitwise

/** A local macro used for testing a shift function */
#define TEST_SHIFT(MASK) binary<Ex::BV, Op::Shift<MASK>, SM::First, Cr::shift<MASK>>();

    Log::debug("Testing shift...");
    {
        using S = Mode::Shift;
        TEST_SHIFT(S::Left);
        TEST_SHIFT(S::ArithmeticRight);
        TEST_SHIFT(S::LogicalRight);
    }

// Cleanup
#undef TEST_SHIFT

    Log::debug("Testing rotate...");
    binary<Ex::BV, Op::Rotate<Mode::LR::Left>, SM::First, Cr::rotate<Mode::LR::Left>>();
    binary<Ex::BV, Op::Rotate<Mode::LR::Right>, SM::First, Cr::rotate<Mode::LR::Right>>();

    // Misc

    Log::debug("Testing widen...");
    binary<Ex::BV, Op::Widen, SM::First, Cr::widen>();

    Log::debug("Testing union...");
    binary<Ex::BV, Op::Union, SM::First, Cr::union_>();

    Log::debug("Testing intersection...");
    binary<Ex::BV, Op::Intersection, SM::First, Cr::intersection_<Expr::BV>>();
    binary<Ex::Bool, Op::Intersection, SM::First, Cr::intersection_<Expr::Bool>>();

    Log::debug("Testing concat...");
    binary<Ex::BV, Op::Concat, SM::Add, Cr::concat<Expr::BV>>();
    binary<Ex::String, Op::Concat, SM::Add, Cr::concat<Expr::String>>();

    /********************************************************************/
    /*                               Flat                               */
    /********************************************************************/

    // Math

    Log::debug("Testing add...");
    flat<Ex::BV, Op::Add, SM::First, Cr::add>();

    Log::debug("Testing mul...");
    flat<Ex::BV, Op::Mul, SM::First, Cr::mul>();

    // Logical

    Log::debug("Testing or...");
    flat<Ex::BV, Op::Or, SM::First, Cr::or_<Expr::BV>>();
    flat<Ex::Bool, Op::Or, SM::First, Cr::or_<Expr::Bool>>();

    Log::debug("Testing and...");
    flat<Ex::BV, Op::And, SM::First, Cr::and_<Expr::BV>>();
    flat<Ex::Bool, Op::And, SM::First, Cr::and_<Expr::Bool>>();

    Log::debug("Testing xor...");
    flat<Ex::BV, Op::Xor, SM::First, Cr::xor_>();
}

// Define the test
UNITTEST_DEFINE_MAIN_TEST(trivial)
