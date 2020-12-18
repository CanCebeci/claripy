/** @file */
#include "bits.hpp"

#include "../../errors/ast.hpp"

#include <sstream>
#include <utility>


// For brevity
using CBits = AST::RawTypes::Bits;


CBits::~Bits() {}

CBits::Bits(const Hash h, const Ops::Operation o, const Constants::Int l)
    : Base(h, o), length(l) {}

/** @todo change this */
AST::Hash CBits::hash(const Ops::Operation o, const Constants::Int l) {
    return l;
}

std::string CBits::type_name() const {
    auto s = std::set<BackendID>();
    std::stringstream ret;
    ret << this->fundamental_type_name() << this->length;
    return ret.str();
}

std::string CBits::fundamental_type_name() const {
    return "AST::Bits";
}

void CBits::check_replaceability(const AST::Bits &old, const AST::Bits &new_) {
    if (old->length != new_->length) {
        throw Errors::AST::Base("Replacements must have matching sizes");
    }
}