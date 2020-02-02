#pragma once

#include "node.h"
#include <jsoncons/json.hpp>

namespace grfc {
    class grafcet final {
    private:
        JSONCONS_TYPE_TRAITS_FRIEND
        const int count = 0;
        const fup::bb building_block;
        const std::vector<grfc::node> nodes;
    public:
        grafcet(const std::vector<grfc::node> _nodes, const fup::bb _building_block = fup::bb::fc1);

        const std::vector<grfc::node> get_node_vec() const;
        void write_as_json_tofile(std::string);
        friend std::ostream& operator<<(std::ostream& os, const grafcet& dt);
    };
}