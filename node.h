#pragma once

#include "transition.h"
#include "expression.h"

namespace grfc {
    class node final {
    private:
        int step, next_step;
        const fup::bb building_block;
        const bool is_initial = false;

        const grfc::transition trans;
        const grfc::expression expr;
        const std::pair<bool, std::shared_ptr<grfc::node>> connected_to_initial;

    public:
        node(bool _is_initial, int _step, const grfc::transition _trans, const grfc::expression _expr, const std::pair<bool, std::shared_ptr<grfc::node>> _connected_to_initial = std::pair<bool, std::shared_ptr<grfc::node>>(false, nullptr), fup::bb _building_block = fup::bb::fc1);
        friend std::ostream& operator<<(std::ostream& os, const node& dt);
    };
}