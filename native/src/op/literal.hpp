/**
 * @file
 * @brief The OP representing a Literal
 */
#ifndef R_OP_LITERAL_HPP_
#define R_OP_LITERAL_HPP_

#include "base.hpp"

#include "../big_int.hpp"
#include "../py_obj.hpp"

#include <cstddef>
#include <variant>


namespace Op {

    /** The op class Literal */
    class Literal final : public Base {
        OP_FINAL_INIT(Literal, 0);

      public:
        /** The value type */
        using Data = std::variant<bool,          // Bool
                                  std::string,   // String
                                  float, double, // FP
                                  PyObj::VSPtr,  // VS
                                  // BV
                                  uint8_t, uint16_t, uint32_t, uint64_t, BigInt>;

        /** Representation */
        const Data value;

        /** Returns the bit_length of the value stored in Data
         *  If Data contains a type that doesn't correspond to an Expr that is a subclass
         *  of BitLength then an Usage exception is thrown
         */
        constexpr UInt bit_length() const {
            if (std::holds_alternative<BigInt>(value)) {
                return std::get<BigInt>(value).bit_length;
            }
            else {
                return C_CHAR_BIT * byte_length();
            }
        }

        /** Python's repr function (outputs json)
         *  @todo This could be a switch-case statement; do when more stable
         */
        inline void repr(std::ostream &out, const bool) const override final {

/** A local macro used for consistency */
#define VCASE_PRE(INDEX, TYPE)                                                                    \
    case (INDEX): {                                                                               \
        UTILS_VARIANT_VERIFY_INDEX_TYPE_IGNORE_CONST(value, INDEX, TYPE)                          \
        const auto &got { std::get<TYPE>(value) };

/** A local macro used for consistency */
#define VCASE_POST                                                                                \
    break;                                                                                        \
    }

/** A local macro used for consistency */
#define VCASE(INDEX, TYPE)                                                                        \
    VCASE_PRE(INDEX, TYPE);                                                                       \
    out << got;                                                                                   \
    VCASE_POST;

            // Repr depending on type
            out << R"|({ "name":")|" << op_name() << R"|(", "value":)|";
            switch (value.index()) {
                // Bool
                VCASE_PRE(0, bool);
                out << std::boolalpha << got;
                VCASE_POST;
                // String
                VCASE_PRE(1, std::string);
                out << std::quoted(got);
                VCASE_POST;
                // FP
                VCASE(2, float);
                VCASE(3, double);
                // VS
                VCASE(4, PyObj::VSPtr);
                // BV
                VCASE_PRE(5, uint8_t);
                out << static_cast<uint16_t>(got); // To avoid printing as a char
                VCASE_POST;
                VCASE(6, uint16_t);
                VCASE(7, uint32_t);
                VCASE(8, uint64_t);
                VCASE_PRE(9, BigInt);
                got.write_value(out);
                out << R"|(, "Bit length":)|" << got.bit_length;
                VCASE_POST;
                    // Bad variant
                default:
                    throw Util::Error::Unknown(WHOAMI_WITH_SOURCE, "unknown type in variant");
            }
            out << " }";

// Cleanup
#undef VCASE_PRE
#undef VCASE_POST
#undef VCASE
        }

        /** Adds the raw expr children of the expr to the given stack in reverse
         *  Warning: This does *not* give ownership, it transfers raw pointers
         */
        inline void add_reversed_children(Stack &) const noexcept override final {}

      private:
/** A local macro used to define a private constructor for Literal */
#define P_CTOR(TYPE)                                                                              \
    /** Private constructor                                                                       \
     *  Literal constructors should never be given shared pointers to nulllptr                    \
     */                                                                                           \
    explicit inline Literal(const Hash::Hash &h, TYPE &&data)                                     \
        : Base { h, static_cuid }, value { std::move(data) }

        // The different private constructors we allow
        // There should be one for each variant type
        P_CTOR(bool) {};
        P_CTOR(std::string) {};
        P_CTOR(float) {};
        P_CTOR(double) {};
        P_CTOR(PyObj::VSPtr) { UTILS_AFFIRM_NOT_NULL_DEBUG(std::get<PyObj::VSPtr>(value)); }
        // BV constructors
        P_CTOR(uint8_t) {};
        P_CTOR(uint16_t) {};
        P_CTOR(uint32_t) {};
        P_CTOR(uint64_t) {};
        P_CTOR(BigInt) {};

// Cleanup
#undef P_CTOR

        /** Returns the byte_length of the value stored in Data
         *  If Data contains a type that doesn't correspond to an Expr that is a subclass
         *  of BitLength then an Usage exception is thrown
         *  This function requires that if value is a shared_ptr is be non-null
         *  This function may not be called on a BigInt
         */
        constexpr UInt byte_length() const {

/** A local macro used for consistency */
#define VCASE_PRE(INDEX, TYPE)                                                                    \
    case (INDEX): {                                                                               \
        UTILS_VARIANT_VERIFY_INDEX_TYPE_IGNORE_CONST(value, INDEX, TYPE)                          \
        const auto &got { std::get<TYPE>(value) };

/** A local macro used for consistency */
#define RET(X)                                                                                    \
    return (X);                                                                                   \
    }

/** A local macro used for consistency */
#define VCASE(INDEX, TYPE)                                                                        \
    VCASE_PRE(INDEX, TYPE);                                                                       \
    RET(sizeof(got));

            switch (value.index()) {
                // String
                VCASE_PRE(1, std::string);
                RET(got.size());
                // FP
                VCASE(2, float);
                VCASE(3, double);
                // VS
                VCASE_PRE(4, PyObj::VSPtr);
#ifdef DEBUG
                UTILS_AFFIRM_NOT_NULL_DEBUG(std::get<PyObj::VSPtr>(value));
                const auto bl { std::get<PyObj::VSPtr>(value)->bit_length };
                Util::affirm<Util::Error::Size>(
                    bl % C_CHAR_BIT == 0, WHOAMI_WITH_SOURCE "VS of bit length ", bl,
                    " which is not divisible by ", C_CHAR_BIT, " aka C_CHAR_BIT");
#endif
                RET(got->bit_length / C_CHAR_BIT);
                // BV
                VCASE(5, uint8_t);
                VCASE(6, uint16_t);
                VCASE(7, uint32_t);
                VCASE(8, uint64_t);
                // Bool
                default: {
                    using Err = Util::Error::Usage;
                    throw Err(WHOAMI_WITH_SOURCE,
                              "invoked when internal type does not correspond"
                              " to an Expr which subclasses BitLength."
                              " Current variant index is: ",
                              value.index());
                };
            }

// Cleanup
#undef VCASE_PRE
#undef RET
#undef VCASE
        }
    };

} // namespace Op

#endif
