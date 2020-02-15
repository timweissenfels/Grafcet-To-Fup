#pragma once
#include <optional>
#include <functional>
#include <jsoncons/json.hpp>

#include "enum_identifier.h"
#include "single_statement.h"
#include "grafcet_timer.h"

namespace grfc {

    class expression final {
    private:
        JSONCONS_TYPE_TRAITS_FRIEND
        const int count_blocks;
        const std::vector<grfc::single_statement> action_block;
        bool has_conditional = false;
    public:
        expression(std::vector<grfc::single_statement>);
        friend std::ostream& operator<<(std::ostream& os, const grfc::expression& dt);
    };
}