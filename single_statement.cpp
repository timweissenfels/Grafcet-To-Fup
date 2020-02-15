#pragma once

#include <string>

#include "single_statement.h"

namespace grfc {
    single_statement::single_statement(const bool _is_inverted, const grfc::identifier _literal_and_num, const grfc::conn _type, std::shared_ptr<grfc::single_statement> _conditional_statement = nullptr, const bool _has_conditional = false)
        : is_inverted(_is_inverted), type(_type), has_conditional(_has_conditional), literal_and_num(std::make_shared<grfc::identifier>(_literal_and_num)), act(grfc::action::set) {
        if (has_conditional) {
            if (_conditional_statement.get()->has_conditional)
                throw std::invalid_argument("A conditional statement cant have a conditinal statement!");
            _conditional_statement.get()->is_conditional = true;
            conditional_statement = _conditional_statement;
        }
    }
    single_statement::single_statement(const bool _is_inverted, const grfc::identifier _literal_and_num, const grfc::action _act, std::shared_ptr<grfc::single_statement> _conditional_statement = nullptr, const bool _has_conditional = false)
        : is_inverted(_is_inverted), act(_act), has_conditional(_has_conditional), literal_and_num(std::make_shared<grfc::identifier>(_literal_and_num)), type(grfc::conn::non) {
        if (has_conditional) {
            if (_conditional_statement.get()->has_conditional)
                throw std::invalid_argument("A conditional statement cant have a conditinal statement!");
            _conditional_statement.get()->is_conditional = true;
            conditional_statement = _conditional_statement;
        }
    }
    single_statement::single_statement(const grfc::grafcet_timer _timer, std::shared_ptr<grfc::single_statement> _conditional_statement = nullptr, const bool _has_conditional = false)
        : is_inverted(false), act(grfc::action::timer), type(grfc::conn::non), timer(std::make_shared<grfc::grafcet_timer>(_timer)) {
        if (has_conditional) {
            if (_conditional_statement.get()->has_conditional)
                throw std::invalid_argument("A conditional statement cant have a conditinal statement!");
            _conditional_statement.get()->is_conditional = true;
            conditional_statement = _conditional_statement;
        }    
    }

    char single_statement::literal() const {
        return literal_and_num.get()->literal;
    }

    int single_statement::num() const {
        return literal_and_num.get()->number;
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