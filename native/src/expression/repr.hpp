/**
 * @file
 * @brief This file defines the repr function for expressions
 * Note that these are not member functions because they require knowledge of op internals
 */
#ifndef __EXPRESSION_REPR_HPP__
#define __EXPRESSION_REPR_HPP__

#include "base.hpp"


namespace Expression {

    /** The repr function for expressions (outputs json) */
    void repr(const Expression::RawPtr e, std::ostringstream &out, const bool verbose = false);

    /** The repr function for expressions (outputs json) */
    inline void repr(const Expression::BasePtr &e, std::ostringstream &out,
                     const bool verbose = false) {
        repr(e.get(), out, verbose);
    }

} // namespace Expression

#endif