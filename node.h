#pragma once

#include "transition.h"
#include "expression.h"
#include <jsoncons/json.hpp>

namespace grfc {
    class node final {
    private:
        JSONCONS_TYPE_TRAITS_FRIEND
        
        int next_step;
        const bool is_initial = false;

        const grfc::transition trans;
        const grfc::expression expr;
        const std::pair<bool, int> connected_to_initial;

    public:
        int step;
        node(bool _is_initial, int _step, const grfc::transition _trans, const grfc::expression _expr, const std::pair<bool, int> _connected_to_initial = std::pair<bool, int>(false, 0));
        friend std::ostream& operator<<(std::ostream& os, const node& dt);
    };
}