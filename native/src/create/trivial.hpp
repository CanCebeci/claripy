/**
 * @file
 * @brief This file defines a group of create methods that are trivial passthrough methods
 * For example: Functions which just shell out to unary, binary, or flat
 */
#ifndef R_CREATE_TRIVIAL_HPP_
#define R_CREATE_TRIVIAL_HPP_

#include "private/binary.hpp"
#include "private/flat.hpp"
#include "private/uint_binary.hpp"
#include "private/unary.hpp"


namespace Create {

    /********************************************************************/
    /*                   Unary Passthrough Functions                    */
    /********************************************************************/

    /** Create an Expression with an Abs op */
    template <typename T> inline EBasePtr abs(const EBasePtr &x, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::unary<T, T, Op::Abs, Ex::BV, Ex::FP>(x, std::move(sp));
    }

    /** Create an Expression with an Neg op */
    template <typename T> inline EBasePtr neg(const EBasePtr &x, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::unary<T, T, Op::Neg, Ex::BV, Ex::FP>(x, std::move(sp));
    }

    /** Create an Expression with an Invert op */
    template <typename T> inline EBasePtr invert(const EBasePtr &x, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::unary<T, T, Op::Invert, Ex::BV, Ex::Bool>(x, std::move(sp));
    }

    /** Create an Expression with an Reverse op */
    inline EBasePtr reverse(const EBasePtr &x, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::unary<Ex::BV, Ex::BV, Op::Reverse, Ex::BV>(x, std::move(sp));
    }

    /********************************************************************/
    /*                 Int Binary Passthrough Functions                 */
    /********************************************************************/

    /** Create an Expression with an SignExt op */
    inline EBasePtr sign_ext(const EBasePtr &expr, const Constants::UInt integer,
                             SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::uint_binary<Constants::UInt, Ex::BV, Op::SignExt, Private::SizeMode::Add,
                                    Ex::BV>(expr, integer, std::move(sp));
    }

    /** Create an Expression with an ZeroExt op */
    inline EBasePtr zero_ext(const EBasePtr &expr, const Constants::UInt integer,
                             SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::uint_binary<Constants::UInt, Ex::BV, Op::ZeroExt, Private::SizeMode::Add,
                                    Ex::BV>(expr, integer, std::move(sp));
    }

    /********************************************************************/
    /*                   Binary Passthrough Functions                   */
    /********************************************************************/

    // Comparisons

    /** Create a Bool Expression with an Eq op */
    template <typename T>
    inline EBasePtr eq(const EBasePtr &left, const EBasePtr &right, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::binary<Ex::Bool, T, Op::Eq, Private::SizeMode::NA, Ex::FP, Ex::Bool,
                               Ex::BV, Ex::String>(left, right, std::move(sp));
    }

    /** Create a Bool Expression with an Neq op */
    template <typename T>
    inline EBasePtr neq(const EBasePtr &left, const EBasePtr &right, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::binary<Ex::Bool, T, Op::Neq, Private::SizeMode::NA, Ex::FP, Ex::Bool,
                               Ex::BV, Ex::String>(left, right, std::move(sp));
    }

    /** Create an Expression with a Compare op */
    template <typename In, Mode::Compare Mask>
    inline EBasePtr compare(const EBasePtr &left, const EBasePtr &right, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        static_assert(Mode::compare_is_valid(Mask), "Invalid Compare Mode");
        if constexpr (Utils::is_same_ignore_const<In, Ex::FP>) {
            static_assert(Utils::BitMask::has(Mask, Mode::Compare::Signed),
                          "FP comparisons must be signed");
        }
        return Private::binary<Ex::Bool, In, Op::Compare<Mask>, Private::SizeMode::NA, Ex::FP,
                               Ex::BV>(left, right, std::move(sp));
    }

    // Math

    /** Create an Expression with an Sub op */
    inline EBasePtr sub(const EBasePtr &left, const EBasePtr &right, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::binary<Ex::BV, Op::Sub, Private::SizeMode::First, Ex::BV>(left, right,
                                                                                  std::move(sp));
    }

    /** Create an Expression with an Div op */
    template <bool Signed>
    inline EBasePtr div(const EBasePtr &left, const EBasePtr &right, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::binary<Ex::BV, Op::Div<Signed>, Private::SizeMode::First, Ex::BV>(
            left, right, std::move(sp));
    }

    /** Create an Expression with an Pow op */
    inline EBasePtr pow(const EBasePtr &left, const EBasePtr &right, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::binary<Ex::BV, Op::Pow, Private::SizeMode::First, Ex::BV>(left, right,
                                                                                  std::move(sp));
    }

    /** Create an Expression with an Mod op */
    template <bool Signed>
    inline EBasePtr mod(const EBasePtr &left, const EBasePtr &right, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::binary<Ex::BV, Op::Mod<Signed>, Private::SizeMode::First, Ex::BV>(
            left, right, std::move(sp));
    }

    // Bitwise

    /** Create an Expression with a Shift op */
    template <Mode::Shift Mask>
    inline EBasePtr arithmetic_shift(const EBasePtr &left, const EBasePtr &right,
                                     SPAV &&sp = nullptr) {
        static_assert(Mode::shift_is_valid(Mask), "Invalid Shift Mode");
        namespace Ex = Expression;
        return Private::binary<Ex::BV, Op::Shift<Mask>, Private::SizeMode::First, Ex::BV>(
            left, right, std::move(sp));
    }

    /** Create an Expression with a Rotate op */
    template <bool Left>
    inline EBasePtr rotate(const EBasePtr &left, const EBasePtr &right, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::binary<Ex::BV, Op::Rotate<Left>, Private::SizeMode::First, Ex::BV>(
            left, right, std::move(sp));
    }

    // Misc

    /** Create an Expression with an Widen op */
    inline EBasePtr widen(const EBasePtr &left, const EBasePtr &right, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::binary<Ex::BV, Op::Widen, Private::SizeMode::First, Ex::BV>(left, right,
                                                                                    std::move(sp));
    }

    /** Create an Expression with an Union op */
    inline EBasePtr union_(const EBasePtr &left, const EBasePtr &right, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::binary<Ex::BV, Op::Union, Private::SizeMode::First, Ex::BV>(left, right,
                                                                                    std::move(sp));
    }

    /** Create an Expression with an Intersection op */
    template <typename T>
    inline EBasePtr intersection_(const EBasePtr &left, const EBasePtr &right,
                                  SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::binary<T, Op::Intersection, Private::first_or_na<T>, Ex::BV, Ex::Bool>(
            left, right, std::move(sp));
    }

    /** Create an Expression with an Concat op */
    template <typename T>
    inline EBasePtr concat(const EBasePtr &left, const EBasePtr &right, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::binary<T, Op::Concat, Private::SizeMode::Add, Ex::BV, Ex::String>(
            left, right, std::move(sp));
    }

    /********************************************************************/
    /*                    Flat Passthrough Functions                    */
    /********************************************************************/

    // Math

    /** Create an Expression with an Add op */
    inline EBasePtr add(Op::Add::OpContainer &&operands, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::flat<Ex::BV, Op::Add, Private::SizeMode::First, Ex::BV>(
            std::move(operands), std::move(sp));
    }

    /** Create an Expression with an Mul op */
    inline EBasePtr mul(Op::Mul::OpContainer &&operands, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::flat<Ex::BV, Op::Mul, Private::SizeMode::First, Ex::BV>(
            std::move(operands), std::move(sp));
    }

    // Logical

    /** Create an Expression with an Or op */
    template <typename T>
    inline EBasePtr or_(Op::Or::OpContainer &&operands, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::flat<T, Op::Or, Private::first_or_na<T>, Ex::BV, Ex::Bool>(
            std::move(operands), std::move(sp));
    }

    /** Create an Expression with an And op */
    template <typename T>
    inline EBasePtr and_(Op::And::OpContainer &&operands, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::flat<T, Op::And, Private::first_or_na<T>, Ex::BV, Ex::Bool>(
            std::move(operands), std::move(sp));
    }

    /** Create an Expression with an Xor op */
    inline EBasePtr xor_(Op::Xor::OpContainer &&operands, SPAV &&sp = nullptr) {
        namespace Ex = Expression;
        return Private::flat<Ex::BV, Op::Xor, Private::SizeMode::First, Ex::BV>(
            std::move(operands), std::move(sp));
    }

} // namespace Create


#endif
