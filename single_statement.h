#pragma once

#include <jsoncons/json.hpp>

#include "enum_identifier.h"
#include "grafcet_timer.h"
namespace grfc {
    class single_statement final {
    private:
        JSONCONS_TYPE_TRAITS_FRIEND
        bool is_conditional = false;
        const bool is_inverted = false, has_conditional = false;
        const grfc::conn type;
        const grfc::action act;
        std::shared_ptr<grfc::identifier> literal_and_num; // example: char='x' , int=1;
        std::shared_ptr<grfc::grafcet_timer> timer;
        std::shared_ptr<grfc::single_statement> conditional_statement;
    public:
        single_statement(const bool, const grfc::identifier, const grfc::conn, std::shared_ptr<grfc::single_statement>, const bool);
        single_statement(const bool, const grfc::identifier, const grfc::action, std::shared_ptr<grfc::single_statement> , const bool);
        single_statement(const grfc::grafcet_timer, const grfc::conn, std::shared_ptr<grfc::single_statement>, const bool);

        char literal() const;
        int num() const;
        grfc::conn conn() const;
        grfc::action action() const;
        std::string full_name() const;
        bool is_invert() const;
    };
}