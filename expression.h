#pragma once

#include <jsoncons/json.hpp>

#include "enum_identifier.h"
#include "single_statement.h"


namespace grfc {
    class expression {
    private:
        JSONCONS_TYPE_TRAITS_FRIEND
        const int count_blocks;
        const std::vector<grfc::single_statement> act_with_literal;
    public:
        expression(std::vector<grfc::single_statement> _act_with_literal);
        friend std::ostream& operator<<(std::ostream& os, const grfc::expression& dt);
    };
}