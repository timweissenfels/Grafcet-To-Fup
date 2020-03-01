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

//For Shared Pointer inside single_statement
JSONCONS_POLYMORPHIC_TRAITS_DECL(grfc::identifier, grfc::identifier)
JSONCONS_POLYMORPHIC_TRAITS_DECL(grfc::grafcet_timer, grfc::grafcet_timer)

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

	for (int node_i = 0; node_i < node_count; node_i++) {
		//INITIAL STEP
		grfc::user_input::CLS();
		std::cout << "Aktuelle Node: " << node_i << std::endl;
		bool _is_node_initial = grfc::user_input::node::get_is_node_initial();

		//STEP NUMBER
		int node_step = node_i;

		//TRANSITION
		grfc::user_input::CLS();
		std::cout << "Aktuelle Node: " << node_i << std::endl;
		bool is_transition_inverted = grfc::user_input::transition::get_is_transition_initial();

		int transition_statement_count = grfc::user_input::transition::get_transition_statement_count();

		std::vector<grfc::single_statement> transition_single_statements_vector;

		for (int transition_statement_i = 0; transition_statement_i < transition_statement_count; transition_statement_i++) {
			bool is_single_statement_inverted = grfc::user_input::single_statement::get_is_single_statement_inverted();

			std::string single_statement_identifier_input = grfc::user_input::single_statement::get_single_statement_identifier_input();

			if (transition_statement_i + 1 < transition_statement_count) {
				int single_statement_conn_input = grfc::user_input::single_statement::get_single_statement_conn_input();

				grfc::conn single_statement_conn = single_statement_conn_input == 1 ? grfc::conn::dot : grfc::conn::plus;

				transition_single_statements_vector.push_back(grfc::single_statement(is_single_statement_inverted, grfc::identifier{ single_statement_identifier_input[0], single_statement_identifier_input.back() - '0' }, single_statement_conn));
			}
			else
				transition_single_statements_vector.push_back(grfc::single_statement(is_single_statement_inverted, grfc::identifier{ single_statement_identifier_input[0], single_statement_identifier_input.back() - '0' }, grfc::conn::non)); //Bugy?
		}

		grfc::transition NODE_TRANSITION(transition_single_statements_vector, is_transition_inverted);
		

		//EXPRESSION
		grfc::user_input::CLS();
		std::cout << "Aktuelle Node: " << node_i << std::endl;
		std::vector<grfc::single_statement> node_expression_vector;

		int expression_block_count = grfc::user_input::expression::get_expression_block_count();

		for (int expression_count_i = 0; expression_count_i < expression_block_count; expression_count_i++) {

			std::string single_statement_identifier_input = grfc::user_input::single_statement::get_single_statement_identifier_input();

			int single_statement_action_input = grfc::user_input::single_statement::get_single_statement_action_input();

			node_expression_vector.push_back(grfc::single_statement(false, grfc::identifier{ single_statement_identifier_input[0], single_statement_identifier_input.back() - '0' }, (grfc::action)single_statement_action_input));
		}

		grfc::expression NODE_EXPRESSION(node_expression_vector);

		//CONNECTED TO INITIAL
		grfc::user_input::CLS();
		std::cout << "Aktuelle Node: " << node_i << std::endl;
		std::pair<bool, int> NODE_CONNECTED_TO_INTITIAL;

		NODE_CONNECTED_TO_INTITIAL.first = grfc::user_input::expression::get_node_connected_to_initial_first();

		if (NODE_CONNECTED_TO_INTITIAL.first) {
			NODE_CONNECTED_TO_INTITIAL.second = grfc::user_input::expression::get_node_connected_to_initial_second();
		}
		else {
			NODE_CONNECTED_TO_INTITIAL.second = 0;
		}

		//NODE
		grfc::user_input::CLS();
		ALL_NODES.push_back(grfc::node(_is_node_initial, node_step, NODE_TRANSITION, NODE_EXPRESSION, NODE_CONNECTED_TO_INTITIAL));
	}

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

	return grfc::grafcet(ALL_NODES, fup::bb::fc1);
#endif
}

int main()
{
	grfc::grafcet first_grfc(cli_interface_get_full_grafcet());

	first_grfc.write_as_json_tofile("Test_Grafcet");

	return 0;
}
