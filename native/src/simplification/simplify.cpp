/** @file */
#include "simplify.hpp"

#include "private/op_map.hpp"

#include "../utils.hpp"


// For brevity
namespace Log = Utils::Log;
namespace Pvt = Simplification::Private;


// Define the simplifications log
UTILS_LOG_DEFINE_LOG_CLASS(Simplify)


Expression::Base Simplification::simplify(const Expression::Base &old) {
#if 0

    if (auto lookup = Pvt::op_map.find(old->op); lookup != Pvt::op_map.end()) {
        return lookup->second(old);
    }
    else {
        Log::verbose<Simplify>("No simplifier for operation: ", old->op);
        return old;
    }
#else
    return old;
#endif
}