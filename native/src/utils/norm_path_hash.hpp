/**
 * @file
 * \ingroup utils
 * @brief This file defines the function norm_path_hash
 */
#ifndef __UTILS_NORMPATHHASH_HPP__
#define __UTILS_NORMPATHHASH_HPP__

#include "affirm.hpp"
#include "error.hpp"
#include "fnv1a.hpp"
#include "str_prefix.hpp"

#include "../constants.hpp"

#include <array>


namespace Utils {

    /** Return the FNV1a of the normal path of s
     *  Len must be the length of s
     */
    template <Constants::UInt Len> constexpr auto norm_path_hash(Constants::CCS s) {

        // Trivial case
        auto len { Len };
        if (len == 0) {
            return static_cast<uint64_t>(0);
        }

/** A local macro used to advance s */
#define ADVANCE(X)                                                                                \
    {                                                                                             \
        s += (X);                                                                                 \
        len -= (X);                                                                               \
    }

        // Determine if absolute or relative path
        const bool absolute { s[0] == '/' };
        if (absolute) {
            while (len && s[0] == '/') {
                ADVANCE(1);
            };
        }

        // Store path segments
        std::array<Constants::CCS, Len> segments {};
        std::array<Constants::UInt, Len> segment_lengths {};
        Constants::UInt n_seg { 0 };

        // Current segment info
        Constants::UInt offset { 0 };
        Constants::UInt current_seg_length { 0 };

        // Repeat for all of s
        while (len) {
            // Handle './' and '//'
            if (str_prefix(s, "./") || str_prefix(s, "//")) {
                ADVANCE(1);
                ++offset;
            }
            // Segment update
            if (s[0] == '/') {
                // Skip empty segments
                if (current_seg_length) {
                    segments[n_seg] = s - offset - current_seg_length;
                    segment_lengths[n_seg] = current_seg_length;
                    ++n_seg;
                }
                // Reset current segment data
                current_seg_length = 0;
                offset = 0;
                ADVANCE(1);
                continue;
            }
            // Handle '../'
            if (str_prefix(s, "../")) {
                ADVANCE(3)
                // Rewinding segments
                affirm<Error::Unexpected::BadPath>(n_seg > 0, WHOAMI_WITH_SOURCE,
                                                   "given path that goes outside of / or ./");
                n_seg -= 1;
                continue;
            }
            // Normal character
            ADVANCE(1)
            ++current_seg_length;
        }

// Cleanup
#undef ADVANCE

        // Record last segment
        segments[n_seg] = s - current_seg_length;
        segment_lengths[n_seg] = current_seg_length;
        ++n_seg;

        // Construct norm path
        std::array<char, Len + 3> norm {};
        Constants::UInt n_len { 0 };
        if (!absolute) {
            norm[n_len++] = '.';
        }
        norm[n_len++] = '/';
        for (Constants::UInt i { 0 }; i < n_seg; ++i) {
            for (Constants::UInt k { 0 }; k < segment_lengths[i]; ++k) {
                norm[n_len++] = static_cast<Constants::CCS>(segments[i])[k];
            }
            norm[n_len++] = '/';
        }
        norm[--n_len] = 0;

        // Hash
        return FNV1a<char>::hash(norm.data(), n_len);
    }

} // namespace Utils

#endif