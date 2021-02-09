/**
 * @file
 * @brief A binary Op; one that takes two inputs of the same type
 * For example: Concat(Str1, Str2)
 */
#ifndef __OP_BINARY_HPP__
#define __OP_BINARY_HPP__

#include "base.hpp"

#include <memory>


namespace Op {

    /** A flattened Op class */
    template <typename T = Expression::Base> class Binary : public Base {
        OP_ASSERT_IS_EXPRESSION(T)
        OP_PURE_INIT(Binary)
      public:
        /** The operand type */
        using Operand = Factory::Ptr<T>;

        /** Left operand */
        const Operand left;
        /** Right operand */
        const Operand right;

      protected:
        /** Protected constructor */
        explicit inline Binary(const Hash::Hash &h, const CUID::CUID &cuid_, const Operand &l,
                               const Operand &r)
            : Base { h, cuid_ }, left { l }, right { r } {}
    };

    /** Default virtual destructor */
    template <typename T> Binary<T>::~Binary() noexcept = default;

} // namespace Op

#endif