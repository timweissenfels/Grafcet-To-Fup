#pragma once

#include <jsoncons/json.hpp>

#include "enum_identifier.h"

namespace grfc {
    class expression {
    private:
        JSONCONS_TYPE_TRAITS_FRIEND
        const int count_blocks;
        const std::vector<std::pair<const grfc::identifier, const grfc::action>> act_with_literal;
    public:
        expression(std::vector<std::pair<const grfc::identifier, const grfc::action>> _act_with_literal);

        const std::vector<std::pair<const grfc::identifier, const grfc::action>> get_act_with_literal_vec() const;

        friend std::ostream& operator<<(std::ostream& os, const grfc::expression& dt);
    };
}