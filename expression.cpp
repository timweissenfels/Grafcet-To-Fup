#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "expression.h"
#include "enum_identifier.h"
#include "single_statement.h"

namespace grfc {
    expression::expression(std::vector<grfc::single_statement> _act_with_literal) : act_with_literal(_act_with_literal), count_blocks(_act_with_literal.size()) {
    }
    expression::expression(std::vector<grfc::single_statement> _act_with_literal, std::vector<grfc::grafcet_timer> _timer) : timer(_timer), act_with_literal(_act_with_literal), count_blocks(_act_with_literal.size() + _timer.size()) {

    }
    expression::expression(std::vector<grfc::grafcet_timer> _timer) : timer(_timer), count_blocks(_timer.size()) {

    }

    std::ostream& operator<<(std::ostream& os, const grfc::expression& dt) {
        std::string str;
        for (auto const& value : dt.act_with_literal) {
            str.push_back(static_cast<char>(value.action()));
            str.push_back(value.literal());
            str.append(std::to_string(value.num()));
            str.push_back(' ');
            str.push_back('|');
        }
        str.pop_back();

        std::cout << str;
        return os;
    }
}