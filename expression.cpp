#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "expression.h"
#include "enum_identifier.h"

namespace grfc {
    expression::expression(std::vector<std::pair<const grfc::identifier, const grfc::action>> _act_with_literal) : act_with_literal(_act_with_literal), count_blocks(_act_with_literal.size()) {

    }

    const std::vector<std::pair<const grfc::identifier, const grfc::action>> grfc::expression::get_act_with_literal_vec() const {
        return act_with_literal;
    }

    std::ostream& operator<<(std::ostream& os, const grfc::expression& dt) {
        std::string str;
        for (auto const& value : dt.act_with_literal) {
            str.push_back(static_cast<char>(value.second));
            str.push_back(value.first.literal);
            str.append(std::to_string(value.first.number));
            str.push_back(' ');
            str.push_back('|');
        }
        str.pop_back();

        std::cout << str;
        return os;
    }
}