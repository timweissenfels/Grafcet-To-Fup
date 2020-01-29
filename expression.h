#pragma once

#include "enum_identifier.h"

namespace grfc {
    class expression {
    private:
        const fup::bb building_block;
        const int count_blocks;
        const std::vector<std::pair<const grfc::identifier, const grfc::action>> act_with_literal;
    public:
        expression(std::vector<std::pair<const grfc::identifier, const grfc::action>> _act_with_literal, fup::bb _building_block = fup::bb::fc1);

        const std::vector<std::pair<const grfc::identifier, const grfc::action>> get_act_with_literal_vec() const;

        friend std::ostream& operator<<(std::ostream& os, const grfc::expression& dt);
    };
}