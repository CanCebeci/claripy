/**
 * @file
 * @brief This file defines a method to create an Expression with an Eq Op
 */
#ifndef R_CREATE_EXTRACT_HPP_
#define R_CREATE_EXTRACT_HPP_

#include "constants.hpp"


namespace Create {

    /** Create an Expression with an Extract op
     *  Expression pointers may not be nullptr
     */
    inline EBasePtr extract(const UInt high, const UInt low, const EBasePtr &from,
                            Annotation::SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        namespace Err = Error::Expression;
        using namespace Simplification;

        // Checks
        Utils::affirm<Err::Usage>(from != nullptr, WHOAMI_WITH_SOURCE "from may not be nullptr");
        Utils::affirm<Err::Type>(CUID::is_t<Ex::BV>(from),
                                 WHOAMI_WITH_SOURCE "from operands must be an Expression::BV");
        Utils::affirm<Err::Type>(high >= low,
                                 WHOAMI_WITH_SOURCE "high should not be lower than low");

        // Construct expression
        return simplify(Ex::factory<Ex::BV>(from->symbolic,
                                            Op::factory<Op::Extract>(high, low, from),
                                            high + 1 - low, std::move(sp)));
    }

} // namespace Create

#endif
