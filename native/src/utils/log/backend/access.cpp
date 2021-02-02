/**
 * @file
 * \ingroup utils
 */
#include "access.hpp"

#include "base.hpp"
#include "default.hpp"

#include "../../thread_safe_access.hpp"


// For brevity
using namespace Utils;
using namespace Log;
using Bk = Backend::Base;


// Create a thread safe backend wrapper
static ThreadSafeAccess<Bk> access(std::make_shared<Backend::Default>());
using Ptr = Constants::SPtr<Backend::Base>;


// Error checking
static_assert(std::is_same_v<Ptr, decltype(access)::Ptr>, "Inconsistiency between pointer types");


void Backend::Private::set(Ptr &ptr) {
    access.set_shared_ptr(ptr);
}

Ptr Backend::get() {
    return access.get();
}
