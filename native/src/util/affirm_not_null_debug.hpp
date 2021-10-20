/**
 * @file
 * \ingroup util
 * @brief This file defines a macro to affirm something is not nullptr when DEBUG is defined
 */
#ifndef R_UTIL_AFFIRMNOTNULLDEBUG_HPP_
#define R_UTIL_AFFIRMNOTNULLDEBUG_HPP_

#include "affirm.hpp"
#include "error.hpp"


#ifdef DEBUG

    /** A macro that null checks (X) iff DEBUG is defined */
    #define UTILS_AFFIRM_NOT_NULL_DEBUG(X)                                                        \
        ::Util::affirm<::Util::Error::Null>((X) != nullptr,                                       \
                                            WHOAMI_WITH_SOURCE "Nullptr detected.");

#else

    /** A macro that nullchecks (X) iff DEBUG is defined */
    #define UTILS_AFFIRM_NOT_NULL_DEBUG(X)

#endif

#endif
