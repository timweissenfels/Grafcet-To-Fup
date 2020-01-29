#pragma once

#include <vector>

#include "enum_identifier.h"
#include "single_statement.h"

namespace grfc {
    class transition final {
    private:
        const std::vector<grfc::single_statement> statements;
        const bool is_inverted = false;
    public:
        transition(const std::vector<grfc::single_statement> _statements, const bool _is_inverted);

        friend std::ostream& operator<<(std::ostream& os, const grfc::transition& dt);
    };
}