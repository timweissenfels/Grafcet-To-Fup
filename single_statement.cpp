#pragma once

#include <string>

#include "single_statement.h"

namespace grfc {
    single_statement::single_statement(const bool _is_inverted, const grfc::identifier _literal_and_num, const grfc::conn _type) : is_inverted(_is_inverted), type(_type), literal_and_num(_literal_and_num), act(grfc::action::set) { }
    single_statement::single_statement(const bool _is_inverted, const grfc::identifier _literal_and_num, const grfc::action _act) : is_inverted(_is_inverted), act(_act), literal_and_num(_literal_and_num), type(grfc::conn::non) { }

    char single_statement::literal() const {
        return literal_and_num.literal;
    }

    int single_statement::num() const {
        return literal_and_num.number;
    }

    grfc::conn single_statement::conn() const {
        return type;
    }

    grfc::action single_statement::action() const {
        return act;
    }

    std::string single_statement::full_name() const {
        return std::string(this->literal(), this->num());
    }

    bool single_statement::is_invert() const {
        return is_inverted;
    }
}