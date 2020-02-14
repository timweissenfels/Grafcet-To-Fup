#pragma once

#include <jsoncons/json.hpp>

#include "enum_identifier.h"
#include "single_statement.h"
#include "grafcet_timer.h"


namespace grfc {
    class expression {
    private:
        JSONCONS_TYPE_TRAITS_FRIEND
        const int count_blocks;
        const std::vector<grfc::single_statement> act_with_literal;
        const std::vector<grfc::grafcet_timer> timer;
    public:
        expression(std::vector<grfc::single_statement>);
        expression(std::vector<grfc::grafcet_timer>);
        expression(std::vector<grfc::single_statement>, std::vector<grfc::grafcet_timer>);
        friend std::ostream& operator<<(std::ostream& os, const grfc::expression& dt);
    };
}