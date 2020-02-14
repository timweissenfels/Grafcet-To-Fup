#pragma once

#include "enum_identifier.h"
#include <jsoncons/json.hpp>

namespace grfc {
    class grafcet_timer final {
    private:
        JSONCONS_TYPE_TRAITS_FRIEND
        const float time;
        const grfc::identifier ident;
        std::string timestr;
    public:
        grafcet_timer(float, int);
    };
}