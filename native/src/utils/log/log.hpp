/**
 * @file
 * @brief This file defines public logging functions
 */
#ifndef __UTILS_LOG_LOG_HPP__
#define __UTILS_LOG_LOG_HPP__

#include "level.hpp"
#include "macros.hpp"
#include "private/level_config.hpp"
#include "private/log.hpp"

#include "../sink.hpp"

#include <utility>


/** A local macro used to define standard log functions */
#define DEFINE_LOG_LEVEL(LEVEL, NAME)                                                             \
    /** Log to default log with given log level */                                                \
    template <typename... Args> void NAME(Args... args) {                                         \
        if constexpr (Private::Enabled::NAME) {                                                   \
            static constexpr LogID id = Default::log_id;                                          \
            Private::backend(id, Level::LEVEL, std::forward<Args>(args)...);                      \
        }                                                                                         \
        else {                                                                                    \
            sink(args...);                                                                        \
        }                                                                                         \
    }                                                                                             \
    /** Log to custom log with given log level */                                                 \
    template <typename Log, typename... Args> void NAME(Args... args) {                           \
        if constexpr (Private::Enabled::NAME) {                                                   \
            static constexpr LogID id = Log::log_id;                                              \
            Private::backend(id, Level::LEVEL, std::forward<Args>(args)...);                      \
        }                                                                                         \
        else {                                                                                    \
            sink(args...);                                                                        \
        }                                                                                         \
    }


namespace Utils::Log {

    /** Define the default log class */
    UTILS_LOG_DEFINE_LOG_CLASS(Default)

    // Define all log functions
    DEFINE_LOG_LEVEL(Verbose, verbose)
    DEFINE_LOG_LEVEL(Debug, debug)
    DEFINE_LOG_LEVEL(Info, info)
    DEFINE_LOG_LEVEL(Warning, warning)
    DEFINE_LOG_LEVEL(Error, error)
    DEFINE_LOG_LEVEL(Critical, critical)

} // namespace Utils::Log

// Cleanup local macros
#undef DEFINE_LOG_LEVEL

#endif