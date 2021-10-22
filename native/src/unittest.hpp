/**
 * @file
 * @brief Forward declares things related to unit testing
 */
#ifndef R_UNITTEST_HPP_
#define R_UNITTEST_HPP_

#ifndef ENABLE_TESTING
    #define ENABLE_UNITTEST_FRIEND_ACCESS
#else

    /** Allows the friend access for unittests */
    #define ENABLE_UNITTEST_FRIEND_ACCESS                                                          \
        /** Allows the friend access for unittests */                                              \
        friend struct UnitTest::ClaricppUnitTest;

namespace UnitTest {

    /** A struct used to give friend access to unittests */
    struct [[maybe_unused]] ClaricppUnitTest;

} // namespace UnitTest

#endif

#endif
