/**
 * @file
 * \ingroup utils
 * @brief This file defines type-dependent constants
 */
#ifndef __UTILS_TYPEDEPENDENTCONSTANT_HPP__
#define __UTILS_TYPEDEPENDENTCONSTANT_HPP__


namespace Utils::TD {

    /** A type-dependent constant type
     *  Because templates are not evaluated until use, this can safely be placed
     *  within a constexpr conditional static_assert without instantly trigging an assertion
     *  failure. Instead, the static_assert will only fail if the line of code is reached
     *  as until that point constant<bool, false, T> is an unevaluated expression, for example.
     */
    template <typename T, T value, typename...> constexpr T constant { value };

    // Abbreviations

    /** A type dependent boolean */
    template <bool Value, typename... _> constexpr bool boolean { constant<bool, Value, _...> };

    /** A type dependent false boolean */
    template <typename... _> constexpr bool false_ { boolean<false, _...> };

} // namespace Utils::TD

#endif
