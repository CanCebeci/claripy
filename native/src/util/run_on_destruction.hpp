/**
 * @file
 * \ingroup util
 * @brief This file defines Util::RunOnDestruction
 */
#ifndef R_UTIL_RUNONDESTRUCTION_HPP_
#define R_UTIL_RUNONDESTRUCTION_HPP_

#include "../macros.hpp"

#include <exception>
#include <functional>


namespace Util {

    /** Runs f() when this is destructed unless disabled
     *  f() must have the type signature: void()
     *  Note: We use the template to permit passing callable objects as well
     *  As such, F can be the return of a lambda, or a callable object, for example
     *  If NoExcept is set to false, the destructor may throw; by default it is true
     */
    template <typename F, bool NoExcept = true> class [[nodiscard]] RunOnDestruction final {
      public:
        /** Constructor */
        explicit RunOnDestruction(const F &func) : f(func) {}

        /** Destructor */
        ~RunOnDestruction() noexcept(NoExcept) {
            if (enabled) {
                if constexpr (NoExcept) {
                    try {
                        f();
                    }
                    // Prevent the program from crashing
                    catch (std::exception &) {
                    }
                }
                else {
                    f();
                }
            }
        }

        /** Enable f on destruction */
        void enable() noexcept { enabled = true; }

        /** Disable f on destruction */
        void disable() noexcept { enabled = false; }

      private:
        // Disable all other methods of construction
        SET_IMPLICITS(RunOnDestruction, delete)

        /** Determine if f should be run on destruction or not
         *  Default: enabled
         */
        bool enabled { true };

        /** The function to be invoked on destruction */
        const std::function<void()> f;
    };

} // namespace Util

#endif
