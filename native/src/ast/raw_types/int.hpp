/**
 * @file
 * @brief This file defines the AST::RawTypes::Int class and defines AST::Int
 */
#ifndef __AST_RAWTYPES_INT_HPP__
#define __AST_RAWTYPES_INT_HPP__

#include "base.hpp"


namespace AST {

    // These types should be wrapped by a shared pointer when used
    // A factory is used to construct them and handle hash caching
    namespace RawTypes {

        /** An AST representing an integer */
        class Int : public Base {
            AST_RAWTYPES_INIT_AST_BASE_SUBCLASS(Int)

            /** A protected constructor to disallow public creation
             *  This must have take in the same arguments types as the hash function, minus the
             * hash These arguments may be taken in via copy, reference or move; ownership is given
             */
            Int(const Hash h, const Op::Operation o);

            /** The hash function of this AST
             *  This must have take in the same arguments as the constructor, minus the hash
             *  These arguments args must be const values or references; this function must be pure
             */
            static Hash hash(const Op::Operation o);
        };

    } // namespace RawTypes

} // namespace AST

#endif