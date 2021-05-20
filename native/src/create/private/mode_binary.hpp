/**
 * @file
 * @brief This file defines a method to create Expressions with standard fp mode binary ops
 */
#ifndef R_CREATE_PRIVATE_MODEBINARY_HPP_
#define R_CREATE_PRIVATE_MODEBINARY_HPP_

#include "size_mode.hpp"

#include "../../mode.hpp"
#include "../constants.hpp"


namespace Create::Private {

    /** Create a Expression with an mode binary op */
    template <typename OpT, SizeMode Mode>
    inline EBasePtr mode_binary(const Expression::BasePtr &left, const Expression::BasePtr &right,
                                const Mode::FP mode, SPAV &&sp) {

        // For brevity
        namespace Ex = Expression;
        using namespace Simplification;
        namespace Err = Error::Expression;

        // Type check
        static_assert(Op::FP::is_mode_binary<OpT>,
                      "Create::Private::mode_binary requires OpT to be Op::FP::ModeBinary");
        Utils::affirm<Err::Type>(CUID::is_t<Ex::FP>(left), WHOAMI_WITH_SOURCE
                                 "left operands must be of type Expression::FP");

        // Create expression
        static_assert(Mode == SizeMode::First,
                      "Create::Private::mode_binary does not support the given SizeMode");
        return simplify(Ex::factory<Ex::FP>(left->symbolic || right->symbolic,
                                            Op::factory<OpT>(left, right, mode),
                                            Ex::get_bit_length(left), std::move(sp)));
    }

} // namespace Create::Private

#endif
