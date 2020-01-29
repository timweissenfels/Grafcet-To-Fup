#pragma once

#include "enum_identifier.h"

namespace grfc {
    class grafcet_timer final {
    private:
        float time;
        fup::bb building_block;
        std::string name;
    public:
        grafcet_timer(float, std::string, fup::bb _building_block = fup::bb::fc1);
    };
}