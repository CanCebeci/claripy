/**
 * @file
 * @brief This file defines Z3 backend constants
 */
#ifndef R_BACKEND_Z3_CONSTANTS_HPP_
#define R_BACKEND_Z3_CONSTANTS_HPP_

#include "../generic.hpp"

#include <map>
#include <string>
#include <z3++.h>


namespace Backend::Z3 {

    /** The 'Generic' superclass of z3 */
    using Super = Generic<z3::expr, false>;

    /** A map used for translocating annotations between symbols
     *  It assists in translocations between pre-conversion and post-abstraction expressions
     */
    using SymAnTransData = std::map<uint64_t, Annotation::SPAV>;

    /** The designated NaN for the given type that the Z3 backend uses */
    template <typename T>
    inline static const constexpr T nan { std::numeric_limits<T>::quiet_NaN() };

    /** A variant of primitives the z3 backend uses */
    using PrimVar = Op::Literal::Data;

    /** What rewriter.hi_fp_unspecified is set to */
    const constexpr bool rhfpu { true };

} // namespace Backend::Z3

#endif
