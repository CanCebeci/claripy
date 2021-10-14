/** \defgroup utils Claricpp Utilities
 * @brief A group of useful classes and methods which all parts of claricpp can utilize
 */

/**
 * @file
 * @brief This file includes all public pieces of utils
 * \ingroup utils
 */
#ifndef R_UTILS_HPP_
#define R_UTILS_HPP_

#include "utils/affirm.hpp"
#include "utils/affirm_not_null_debug.hpp"
#include "utils/ansi_color_codes.hpp"
#include "utils/avg.hpp"
#include "utils/backtrace.hpp"
#include "utils/bitmask.hpp"
#include "utils/c_heap_cache.hpp"
#include "utils/checked_static_cast.hpp"
#include "utils/const_eval.hpp"
#include "utils/declare.hpp"
#include "utils/demangle.hpp"
#include "utils/dependent_constant.hpp"
#include "utils/do_once.hpp"
#include "utils/error.hpp"
#include "utils/file_line_hash.hpp"
#include "utils/fnv1a.hpp"
#include "utils/full.hpp"
#include "utils/function.hpp"
#include "utils/has_constructor.hpp"
#include "utils/hex_to_num.hpp"
#include "utils/inc.hpp"
#include "utils/internal_type.hpp"
#include "utils/is_ancestor.hpp"
#include "utils/is_in.hpp"
#include "utils/is_same.hpp"
#include "utils/is_shared_ptr.hpp"
#include "utils/is_strong_enum.hpp"
#include "utils/log.hpp"
#include "utils/macros.hpp"
#include "utils/make_derived_shared.hpp"
#include "utils/map_add.hpp"
#include "utils/max.hpp"
#include "utils/min.hpp"
#include "utils/narrow.hpp"
#include "utils/norm_path_hash.hpp"
#include "utils/ostream.hpp"
#include "utils/pointer_cast.hpp"
#include "utils/pow.hpp"
#include "utils/range_to_str.hpp"
#include "utils/recurrence_guard.hpp"
#include "utils/ref.hpp"
#include "utils/run_after_main.hpp"
#include "utils/run_before_main.hpp"
#include "utils/run_on_destruction.hpp"
#include "utils/safe_alloc.hpp"
#include "utils/select.hpp"
#include "utils/set_join.hpp"
#include "utils/sfinae_test.hpp"
#include "utils/sign.hpp"
#include "utils/sink.hpp"
#include "utils/stack_limit.hpp"
#include "utils/str_prefix.hpp"
#include "utils/strlen.hpp"
#include "utils/thread_safe.hpp"
#include "utils/to_hex.hpp"
#include "utils/to_str.hpp"
#include "utils/to_underlying.hpp"
#include "utils/transfer_const.hpp"
#include "utils/type_id.hpp"
#include "utils/type_pun.hpp"
#include "utils/type_to_type.hpp"
#include "utils/unconstructable.hpp"
#include "utils/variant_verify_index_type_is.hpp"
#include "utils/verify_syscall.hpp"
#include "utils/weak_cache.hpp"
#include "utils/widen.hpp"

#endif
