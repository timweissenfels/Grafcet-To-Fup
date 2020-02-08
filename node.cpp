#pragma once

#include <iostream>

#include "node.h"

namespace grfc {
    grfc::node::node(bool _is_initial, int _step, const grfc::transition _trans, const grfc::expression _expr, const std::pair<bool, int> _connected_to_initial)
        : step(_step), trans(_trans), expr(_expr), connected_to_initial(_connected_to_initial), is_initial(_is_initial)
    {
        if (this->connected_to_initial.first)
            this->next_step = this->connected_to_initial.second;
        else
            this->next_step = this->step + 1;

    }

    std::ostream& operator<<(std::ostream& os, const node& dt)
    {
        std::cout << "Step: " << dt.step << std::endl;
        std::cout << "Next Step: " << dt.next_step << std::endl;
        std::cout << "Is Initial: " << dt.is_initial << std::endl;
        std::cout << "Expression: " << dt.expr << std::endl;
        std::cout << "Transition: " << dt.trans << std::endl;
        std::cout << "Is Connected to Inital: " << dt.connected_to_initial.first << std::endl;
        return os;
    }
}