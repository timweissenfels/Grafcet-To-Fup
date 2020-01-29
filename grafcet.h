#pragma once

#include "node.h"

namespace grfc {
    class grafcet final {
    private:
        const int count = 0;
        const fup::bb building_block;
        const std::vector<grfc::node> nodes;
    public:
        grafcet(const std::vector<grfc::node> _nodes, const fup::bb _building_block = fup::bb::fc1);

        const std::vector<grfc::node> get_node_vec() const;

        friend std::ostream& operator<<(std::ostream& os, const grafcet& dt);
    };
}