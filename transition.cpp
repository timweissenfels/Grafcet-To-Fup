#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "transition.h"

namespace grfc {

    transition::transition(const std::vector<grfc::single_statement> _statements, const bool _is_inverted) : statements(_statements), is_inverted(_is_inverted) {
    }
    
    transition::transition(const std::vector<grfc::grafcet_timer> _timer) : timer(_timer), is_inverted(false) {
    }
    
    transition::transition(const std::vector<grfc::single_statement> _statements,const std::vector<grfc::grafcet_timer> _timer) : statements(_statements), timer(_timer), is_inverted(false) {
    }

    std::ostream& operator<<(std::ostream& os, const grfc::transition& dt) {
        std::string str;
        if (dt.is_inverted)
            str.push_back('!');
        bool in_brackets = false;

        for (auto const& value : dt.statements) {
            if (value.is_invert())
                str += "!";

            str.push_back(value.literal());
            str += std::to_string(value.num());
            str += " ";
            str.push_back(static_cast<char>(value.conn()));
            str += value.conn() != grfc::conn::non ? " " : "";
        }
        std::cout << str;
        return os;
    }

}