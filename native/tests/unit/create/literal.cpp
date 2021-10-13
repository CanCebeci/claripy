/**
 * @file
 * \ingroup unittest
 */
#include "create.hpp"
#include "dcast.hpp"
#include "testlib.hpp"


/** Test the literal create function with type T */
template <typename T, typename Data>
void literal_t(const Data data, const Constants::UInt size = 0) {

    // Test
    const auto lit { Create::literal(Data { data }) };

    // Pointer checks
    // Note: Bool true and false are used in the backend so their count should be 2
    UNITTEST_ASSERT(lit.use_count() == (std::is_same_v<Data, bool> ? 2 : 1));
    UNITTEST_ASSERT(lit->op.use_count() == 1);

    // Symbolic check
    UNITTEST_ASSERT(not lit->symbolic);

    // Type check
    const auto op_down { dcast<Op::Literal>(lit->op) };
    const auto exp_down { dcast<T>(lit) };

    // Contains check
    UNITTEST_ASSERT(std::get<Data>(op_down->value) == data);

    // Size check
    if constexpr (Utils::is_ancestor<Expression::Bits, T>) {
        UNITTEST_ASSERT(exp_down->bit_length == size)
    }

    // For compilation
    (void) size;
}

/** Test the literal create function */
void literal() {
    static_assert(sizeof(std::byte) == sizeof(char), "std::byte is wonky");

    // Bool
    literal_t<Expression::Bool>(true);

    // String
    std::string data_s { "This is a test" };
    literal_t<Expression::String>(data_s, C_CHAR_BIT * data_s.size());

    // FP
    literal_t<Expression::FP>(3.4, 64_ui);  // NOLINT
    literal_t<Expression::FP>(3.4f, 32_ui); // NOLINT

    // VS
    auto ptr { std::make_shared<const PyObj::VS>(1, 1, C_CHAR_BIT) };
    const auto bl { ptr->bit_length };
    literal_t<Expression::VS>(std::move(ptr), bl);

    // BV
    Create::literal(uint8_t { 3 });
    Create::literal(uint16_t { 3 });
    Create::literal(uint32_t { 3 });
    Create::literal(uint64_t { 3 });
    const boost::multiprecision::mpz_int big { 4 }; // NOLINT
    Create::literal(BigInt { big, 200_ui });        // NOLINT
}

// Define the test
UNITTEST_DEFINE_MAIN_TEST(literal)