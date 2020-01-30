#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <fstream>
#include <map>
#include <tuple>
#include <jsoncons/json.hpp>
#include <jsoncons/encode_decode_json.hpp>

#include "enum_identifier.h"
#include "single_statement.h"
#include "transition.h"
#include "expression.h"
#include "node.h"
#include "grafcet.h"
#include "grafcet_timer.h"

//FUNCTIONPLAN BUILDING BLOCK ENUM
JSONCONS_ENUM_TRAITS_DECL(fup::bb, fc1, fc2, fc3)
//GRAFCET CONN ENUM
JSONCONS_ENUM_TRAITS_DECL(grfc::conn, non, dot, plus)
//GRAFCET ACTION ENUM
JSONCONS_ENUM_TRAITS_DECL(grfc::action, set, unset, rising_edge, falling_edge)
//GRAFCET IDENTIFIER STRUCT
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::identifier, literal, number)
//GRAFCET SINGLE_STATEMENT CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::single_statement, is_inverted, type, literal_and_num)
//GRAFCET TRANSITION CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::transition, statements, is_inverted)
//GRAFCET EXPRESSION CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::expression, count_blocks, act_with_literal)
//GRAFCET NODE CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::node, step, next_step, is_initial, trans, expr, connected_to_initial)
//GRAFCET GRAFCET CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::grafcet, count, building_block, nodes)
//GRAFCET GRAFCET_TIMER CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::grafcet_timer, time, building_block, name)

void ReplaceStringInPlace(std::string& subject, const std::string& search,
    const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
}

void grfc::grafcet::write_as_json_tofile(std::string name) {
    jsoncons::json j;
    std::string name_outfile = name + ".json";

    std::ofstream outfile;
    outfile.open(name_outfile);

    jsoncons::json_stream_encoder encoder(outfile);
    encoder.begin_object();
    for (auto& value : nodes) {
        std::string object_name = "M120.";
        object_name.append(std::to_string(value.step));
        encoder.name(object_name);
        encode_json(value, encoder);
    }
    encoder.end_object();
    encoder.flush();

    outfile.close();
}

int main()
{
    std::vector<grfc::single_statement> x = { 
        grfc::single_statement(false, grfc::identifier{'S',1},grfc::conn::dot), grfc::single_statement(false,grfc::identifier{'S',2},grfc::conn::plus), grfc::single_statement(true,grfc::identifier{'S',3})
    };
    
    grfc::transition transition_test(x,true);
    
    grfc::expression c(std::vector<std::pair<const grfc::identifier, const grfc::action>> { 
        std::pair<const grfc::identifier, const grfc::action>{grfc::identifier{'x', 1},grfc::action::unset},
        std::pair<const grfc::identifier, const grfc::action>{grfc::identifier{'x', 2}, grfc::action::unset}      
    });


    auto vf = std::vector<grfc::node>{ grfc::node(true, 1, transition_test, c),grfc::node(false, 2, transition_test, c) };

    vf.push_back(grfc::node(false, 3, transition_test, c, std::pair<bool, int>{true, 1}));

    grfc::grafcet first_grfc(vf);
       
    first_grfc.write_as_json_tofile("Test_Grafcet");


    //TODO: WIE STD::VEKTOR MIT TYP PRINTEN MIT TO_JSON

    return 0;
}