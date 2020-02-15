#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "expression.h"
#include "enum_identifier.h"
#include "single_statement.h"

namespace grfc {
    expression::expression(std::vector<grfc::single_statement> _action_block) : action_block(_action_block), count_blocks(_action_block.size()) {
    }

    std::ostream& operator<<(std::ostream& os, const grfc::expression& dt) {
        std::string str;
        for (auto const& value : dt.action_block) {
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