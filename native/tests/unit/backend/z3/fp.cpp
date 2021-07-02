/**
 * @file
 * \ingroup unittest
 */
#include "backend.hpp"
#include "testlib.hpp"

#include <limits>


/** Test normal ops in claricpp
 *  @todo: Enable string symbol testing
 */
void fp() {
    namespace Ex = Expression;
    namespace C = Create;

    // The backend
    Backend::Z3::Z3 z3bk;

    // For brevity
    using NLF = std::numeric_limits<float>;
    using NLD = std::numeric_limits<double>;

    const auto fp_x { C::symbol<Ex::FP>("fp_x", Mode::FP::dbl.width()) };
    const auto fp_y { C::symbol<Ex::FP>("fp_y", Mode::FP::dbl.width()) };
    const auto nan { C::literal(std::numeric_limits<double>::quiet_NaN()) };

    // Verify the round trip changes nothing
    const auto test_id = [&z3bk](const Expression::BasePtr &&x) {
        return z3bk.abstract(z3bk.convert(x)) == x;
    };

    /**************************************************/
    /*                    Literals                    */
    /**************************************************/

    Utils::Log::debug("Sanity checks...");
    UNITTEST_ASSERT(NLD::has_signaling_NaN);
    UNITTEST_ASSERT(NLF::has_signaling_NaN);
    UNITTEST_ASSERT(NLD::has_quiet_NaN);
    UNITTEST_ASSERT(NLF::has_quiet_NaN);
    UNITTEST_ASSERT(NLD::has_infinity);
    UNITTEST_ASSERT(NLF::has_infinity);
    UNITTEST_ASSERT(NLD::has_denorm);
    UNITTEST_ASSERT(NLF::has_denorm);
    UNITTEST_ASSERT(NLD::is_iec559);
    UNITTEST_ASSERT(NLF::is_iec559);

    Utils::Log::debug("Testing 0...");
    UNITTEST_ASSERT(test_id(C::literal(0.)));
    UNITTEST_ASSERT(test_id(C::literal(-0.)));
    UNITTEST_ASSERT(test_id(C::literal(0.F)));
    UNITTEST_ASSERT(test_id(C::literal(-0.F)));

    Utils::Log::debug("Testing Inf...");
    UNITTEST_ASSERT(test_id(C::literal(NLD::infinity())));
    UNITTEST_ASSERT(test_id(C::literal(-NLD::infinity())));
    UNITTEST_ASSERT(test_id(C::literal(NLF::infinity())));
    UNITTEST_ASSERT(test_id(C::literal(-NLF::infinity())));

    Utils::Log::debug("Testing NaN...");
    UNITTEST_ASSERT(test_id(C::literal(NLD::quiet_NaN())));
    UNITTEST_ASSERT(test_id(C::literal(NLF::quiet_NaN())));

    const auto test_snan = [&z3bk](const bool is_double) {
        const auto s { is_double ? C::literal(NLD::signaling_NaN())
                                 : C::literal(NLF::signaling_NaN()) };
        const auto *const op_s { dynamic_cast<Constants::CTSC<Op::Literal>>(s->op.get()) };
        UNITTEST_ASSERT(op_s != nullptr);
        // Verify cycled expr
        const auto cycled { z3bk.abstract(z3bk.convert(s)) };
        UNITTEST_ASSERT(Ex::are_same_type<true>(cycled, s));
        // Verify cycled op
        const auto *const op { dynamic_cast<Constants::CTSC<Op::Literal>>(cycled->op.get()) };
        UNITTEST_ASSERT(op != nullptr);
        // Verify cycled value
        if (is_double) {
            const auto *const d_ptr { std::get_if<double>(&(op->value)) };
            UNITTEST_ASSERT(d_ptr != nullptr);
            UNITTEST_ASSERT(std::isnan(*d_ptr));
        }
        else {
            const auto *const f_ptr { std::get_if<float>(&(op->value)) };
            UNITTEST_ASSERT(f_ptr != nullptr);
            UNITTEST_ASSERT(std::isnan(*f_ptr));
        }
        return true;
    };
    UNITTEST_ASSERT(test_snan(true));
    UNITTEST_ASSERT(test_snan(false));

    Utils::Log::debug("Testing subnormals...");
    UNITTEST_ASSERT(test_id(C::literal(NLD::denorm_min())));
    UNITTEST_ASSERT(test_id(C::literal(-NLD::denorm_min())));
    UNITTEST_ASSERT(test_id(C::literal(NLF::denorm_min())));
    UNITTEST_ASSERT(test_id(C::literal(-NLF::denorm_min())));

    Utils::Log::debug("Testing normals...");
    const std::vector<double> normals {
        .00001, .125, .5, .75, 1., 2., 4., 5., 34., 1209342.
    }; // NOLINT
    for (const double i : normals) {
        UNITTEST_ASSERT(test_id(C::literal(i)));
        UNITTEST_ASSERT(test_id(C::literal(-i)));
        UNITTEST_ASSERT(test_id(C::literal(float(i))));
        UNITTEST_ASSERT(test_id(C::literal(-float(i))));
    }

    /**************************************************/
    /*                  Non-Trivial                   */
    /**************************************************/

    /**************************************************/
    /*                    Trivial                     */
    /**************************************************/


    auto conv { z3bk.convert(C::FP::to_ieee_bv(fp_x)) };
    Utils::Log::warning(conv);
    auto abs { z3bk.abstract(conv) };
    Utils::Log::warning(abs);

#if 0
    /** Create a Expression with an FP::ToIEEEBV op
     *  Expression pointers may not be nullptr
     */
    inline EBasePtr to_ieee_bv(const EBasePtr &x, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::unary<Ex::BV, Ex::FP, Op::FP::ToIEEEBV, Ex::FP>(x, std::move(sp));
    }

    #define FP_MB_SMF_ARITH(FN, OP)                                                               \
        inline EBasePtr FN(const EBasePtr &left, const EBasePtr &right,                           \
                           const Mode::FP::Rounding mode, SPAV &&sp = nullptr) {                  \
            return Private::mode_binary<Op::FP::OP, Private::SizeMode::First>(left, right, mode,  \
                                                                              std::move(sp));     \
        }

    /** Create a Expression with an FP::Add op
     *  Expression pointers may not be nullptr
     */
    FP_MB_SMF_ARITH(add, Add);
    /** Create a Expression with an FP::Sub op
     *  Expression pointers may not be nullptr
     */
    FP_MB_SMF_ARITH(sub, Sub);
    /** Create a Expression with an FP::Mul op
     *  Expression pointers may not be nullptr
     */
    FP_MB_SMF_ARITH(mul, Mul);
    /** Create a Expression with an FP::Div op
     *  Expression pointers may not be nullptr
     */
    FP_MB_SMF_ARITH(div, Div);

    inline EBasePtr fp(const EBasePtr &first, const EBasePtr &second, const EBasePtr &third,
                       SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::ternary<Ex::FP, Ex::BV, Op::FP::FP, Private::SizeMode::Add, Ex::BV>(
            first, second, third, std::move(sp));
    }
#endif
}

// Define the test
UNITTEST_DEFINE_MAIN_TEST(fp)