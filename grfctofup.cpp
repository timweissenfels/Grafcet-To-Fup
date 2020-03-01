#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <fstream>
#include <map>
#include <tuple>
#include <jsoncons/json.hpp>
#include <jsoncons/encode_json.hpp>
#include <jsoncons/decode_json.hpp>

#include "enum_identifier.h"
#include "single_statement.h"
#include "transition.h"
#include "expression.h"
#include "node.h"
#include "grafcet.h"
#include "grafcet_timer.h"
#include "user_input.h"

#define _AUTO_DEBUGING_ 1
//#define _USER_TESTING_ 1

//FUNCTIONPLAN BUILDING BLOCK ENUM
JSONCONS_ENUM_TRAITS_DECL(fup::bb, fc1, fc2, fc3)
//GRAFCET CONN ENUM
JSONCONS_ENUM_TRAITS_DECL(grfc::conn, non, dot, plus)
//GRAFCET ACTION ENUM
JSONCONS_ENUM_TRAITS_DECL(grfc::action, set, unset, timer, rising_edge, falling_edge)
//GRAFCET IDENTIFIER STRUCT
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::identifier, literal, number)
//GRAFCET SINGLE_STATEMENT CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::single_statement, is_inverted, type, act, literal_and_num,timer)
//GRAFCET TRANSITION CLASS 
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::transition, statements,is_inverted)
//GRAFCET EXPRESSION CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::expression, count_blocks, action_block)
//GRAFCET NODE CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::node, step, next_step, is_initial, trans, expr, connected_to_initial)
//GRAFCET GRAFCET CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::grafcet, count, building_block, nodes)
//GRAFCET GRAFCET_TIMER CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::grafcet_timer, timestr, time, ident)
//GRAFCET LOGIC_GATE CLASS
//JSONCONS_TPL_ALL_MEMBER_TRAITS_DECL(2,grfc::logic_gate,A_ELEMENT,B_ELEMENT)
//For Shared Pointer inside single_statement
JSONCONS_POLYMORPHIC_TRAITS_DECL(grfc::identifier, grfc::identifier)
JSONCONS_POLYMORPHIC_TRAITS_DECL(grfc::grafcet_timer, grfc::grafcet_timer)
JSONCONS_POLYMORPHIC_TRAITS_DECL(std::string,std::string)
//JSONCONS_POLYMORPHIC_TRAITS_DECL(grfc::logic_gate, grfc::logic_gate)

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

grfc::grafcet cli_interface_get_full_grafcet() {

#if defined _USER_TESTING_ 

	int node_count = grfc::user_input::node::get_node_count();

	//NODES
	std::vector<grfc::node> ALL_NODES;



	return grfc::grafcet(ALL_NODES, fup::bb::fc1);

#elif defined _AUTO_DEBUGING_

	std::vector<grfc::single_statement> trans_statement = {
	grfc::single_statement(grfc::grafcet_timer(3.0,2,grfc::conn::non),grfc::conn::dot,nullptr,false), grfc::single_statement(false,grfc::identifier{'S',2},grfc::conn::plus,nullptr,false), grfc::single_statement(true,grfc::identifier{'S',3},grfc::conn::non,nullptr,false) };

	grfc::transition transition_test(trans_statement,false);

	std::vector<grfc::single_statement> expr{
		grfc::single_statement(false,grfc::identifier{ 'x', 1 }, grfc::action::unset,nullptr,false),
		grfc::single_statement(grfc::grafcet_timer(2.0,4),grfc::conn::non,nullptr,false)
	};

	grfc::expression c(expr);

	auto ALL_NODES = std::vector<grfc::node>{ grfc::node(true, 1, transition_test, c),grfc::node(false, 2, transition_test, c),grfc::node(false, 3, transition_test, c),grfc::node(false, 4, transition_test, c) };

	ALL_NODES.push_back(grfc::node(false, 5, transition_test, c, std::pair<bool, int>{true, 1}));
	get_user_input();
	return grfc::grafcet(ALL_NODES, fup::bb::fc1);
#endif
}

int main()
{
	grfc::grafcet first_grfc(cli_interface_get_full_grafcet());

	first_grfc.write_as_json_tofile("Test_Grafcet");

	return 0;
}