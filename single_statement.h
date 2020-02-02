#pragma once

#include <jsoncons/json.hpp>

#include "enum_identifier.h"

namespace grfc {
    class single_statement final {
    private:
        JSONCONS_TYPE_TRAITS_FRIEND
        const bool is_inverted = false;
        const grfc::conn type;
        const grfc::action act;
        const grfc::identifier literal_and_num; // example: char='x' , int=1;
    public:
        single_statement(const bool _is_inverted, const grfc::identifier _literal_and_num, const grfc::conn _type = grfc::conn::non);
        single_statement(const bool _is_inverted, const grfc::identifier _literal_and_num, const grfc::action _act = grfc::action::set);

        char literal() const;
        int num() const;
        grfc::conn conn() const;
        grfc::action action() const;
        std::string full_name() const;
        bool is_invert() const;
    };
}