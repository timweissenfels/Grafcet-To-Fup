#pragma once

#include <vector>
#include <jsoncons/json.hpp>

#include "enum_identifier.h"
#include "single_statement.h"
#include "grafcet_timer.h"

namespace grfc {
    class transition final {
    private:
        JSONCONS_TYPE_TRAITS_FRIEND
        const std::vector<grfc::single_statement> statements;
        const bool is_inverted = false;
    public:
        transition(const std::vector<grfc::single_statement>, const bool);
        friend std::ostream& operator<<(std::ostream& os, const grfc::transition& dt);
    };
}