#pragma once
#include <vector>
#include <iostream>

#include "grafcet.h"

namespace grfc {
    grafcet::grafcet(const std::vector<grfc::node> _nodes, const fup::bb _building_block) : nodes(_nodes), building_block(_building_block) {

    }

    const std::vector<grfc::node> grafcet::get_node_vec() const{
        return nodes;
    }
    std::ostream& operator<<(std::ostream& os, const grafcet& dt)
    {
        for (auto const& value : dt.nodes) {
            std::cout << value << std::endl;
        }

        return os;
    }
}