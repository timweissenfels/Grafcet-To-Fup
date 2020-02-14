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

#define _AUTO_DEBUGING_ 1
//#define _USER_TESTING_ 1

//FUNCTIONPLAN BUILDING BLOCK ENUM
JSONCONS_ENUM_TRAITS_DECL(fup::bb, fc1, fc2, fc3)
//GRAFCET CONN ENUM
JSONCONS_ENUM_TRAITS_DECL(grfc::conn, non, dot, plus)
//GRAFCET ACTION ENUM
JSONCONS_ENUM_TRAITS_DECL(grfc::action, set, unset, rising_edge, falling_edge)
//GRAFCET IDENTIFIER STRUCT
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::identifier, literal, number)
//GRAFCET SINGLE_STATEMENT CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::single_statement, is_inverted, type, act, literal_and_num)
//GRAFCET TRANSITION CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::transition, statements, timer,is_inverted)
//GRAFCET EXPRESSION CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::expression, count_blocks, act_with_literal, timer)
//GRAFCET NODE CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::node, step, next_step, is_initial, trans, expr, connected_to_initial)
//GRAFCET GRAFCET CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::grafcet, count, building_block, nodes)
//GRAFCET GRAFCET_TIMER CLASS
JSONCONS_ALL_MEMBER_TRAITS_DECL(grfc::grafcet_timer, timestr, time, ident)

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

//Clears Console
void CLS()
{
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
#endif
}

grfc::grafcet cli_interface_get_full_grafcet() {

#if defined _USER_TESTING_ 
	int node_count = 0;
	std::cout << "Anzahl der Nodes: ";
	std::cin >> node_count;

	//NODES
	std::vector<grfc::node> ALL_NODES;

	for (int node_i = 0; node_i < node_count; node_i++) {
		//INITIAL STEP
		CLS();
		std::cout << "Aktuelle Node: " << node_i << std::endl;
		bool _is_node_initial = false;
		std::cout << "Ist die Node der Initial Schritt ( 1:Ja | 0:Nein ): ";
		std::cin >> _is_node_initial;
		std::cout << std::endl;

		//STEP NUMBER
		int node_step = node_i;

		//TRANSITION
		CLS();
		std::cout << "Aktuelle Node: " << node_i << std::endl;
		bool is_transition_inverted = false;
		std::cout << "Soll die Transition Invertiert sein ( 1:Ja | 0:Nein ): ";
		std::cin >> is_transition_inverted;

		int transition_statement_count = 0;
		std::cout << "Anzahl der Bedingungen in der Transition: ";
		std::cin >> transition_statement_count;

		std::vector<grfc::single_statement> transition_single_statements_vector;

		for (int transition_statement_i = 0; transition_statement_i < transition_statement_count; transition_statement_i++) {
			bool is_single_statement_inverted = false;
			std::cout << "Ist das Statement Invertiert ( 1:Ja | 0:Nein ):";
			std::cin >> is_single_statement_inverted;

			std::string single_statement_identifier_input;
			std::cout << "Geben Sie EINEN Bezeichner ein (BuchstabeZahl) Beispiel(x1,S2,P3): ";
			std::cin >> single_statement_identifier_input;

			if (transition_statement_i + 1 < transition_statement_count) {
				int single_statement_conn_input = 0;
				std::cout << "Welche Verbindung besteht zum naechsten Bezeichner (1:Und-Verknuepfung | 2:Oder-Verknuepfung): ";
				std::cin >> single_statement_conn_input;

				grfc::conn single_statement_conn = single_statement_conn_input == 1 ? grfc::conn::dot : grfc::conn::plus;

				transition_single_statements_vector.push_back(grfc::single_statement(is_single_statement_inverted, grfc::identifier{ single_statement_identifier_input[0], single_statement_identifier_input.back() - '0' }, single_statement_conn));
			}
			else
				transition_single_statements_vector.push_back(grfc::single_statement(is_single_statement_inverted, grfc::identifier{ single_statement_identifier_input[0], single_statement_identifier_input.back() - '0' }, grfc::conn::non)); //Bugy?
		}

		grfc::transition NODE_TRANSITION(transition_single_statements_vector, is_transition_inverted);

		//EXPRESSION
		CLS();
		std::cout << "Aktuelle Node: " << node_i << std::endl;
		std::vector<grfc::single_statement> node_expression_vector;

		int expression_block_count = 0;
		std::cout << "Anzahl der Aktionen der Node: ";
		std::cin >> expression_block_count;

		for (int expression_count_i = 0; expression_count_i < expression_block_count; expression_count_i++) {

			std::string single_statement_identifier_input;
			std::cout << "Geben Sie EINEN Bezeichner ein (BuchstabeZahl) Beispiel(x1,S2,P3): ";
			std::cin >> single_statement_identifier_input;

			int single_statement_action_input = 0;
			std::cout << "Geben Sie EINE Aktion ein ( 0:Setzen | 1:Nicht-setzen ): ";
			std::cin >> single_statement_action_input;
			node_expression_vector.push_back(grfc::single_statement(false, grfc::identifier{ single_statement_identifier_input[0], single_statement_identifier_input.back() - '0' }, (grfc::action)single_statement_action_input));
		}

		grfc::expression NODE_EXPRESSION(node_expression_vector);

		//CONNECTED TO INITIAL
		CLS();
		std::cout << "Aktuelle Node: " << node_i << std::endl;
		std::pair<bool, int> NODE_CONNECTED_TO_INTITIAL;

		std::cout << "Ist der Schritt mit dem Initial Schritt verbunden sein ( 1:Ja | 0:Nein ): ";
		std::cin >> NODE_CONNECTED_TO_INTITIAL.first;

		if (NODE_CONNECTED_TO_INTITIAL.first) {
			std::cout << "Welche Nummer hat der Schritt: ";
			std::cin >> NODE_CONNECTED_TO_INTITIAL.second;
		}
		else {
			NODE_CONNECTED_TO_INTITIAL.second = 0;
		}

		//NODE
		CLS();
		ALL_NODES.push_back(grfc::node(_is_node_initial, node_step, NODE_TRANSITION, NODE_EXPRESSION, NODE_CONNECTED_TO_INTITIAL));
	}

	return grfc::grafcet(ALL_NODES, fup::bb::fc1);

#elif defined _AUTO_DEBUGING_

	std::vector<grfc::single_statement> trans_statement = {
	grfc::single_statement(false, grfc::identifier{'S',1},grfc::conn::dot), grfc::single_statement(false,grfc::identifier{'S',2},grfc::conn::plus), grfc::single_statement(true,grfc::identifier{'S',3},grfc::conn::non) };

	std::vector<grfc::grafcet_timer> trans_timer = {
		grfc::grafcet_timer(2.0,1,grfc::conn::plus),
		grfc::grafcet_timer(3.0,2,grfc::conn::non)
	};

	grfc::transition transition_test(trans_statement, trans_timer);

	std::vector<grfc::single_statement> expr{
		grfc::single_statement(false,grfc::identifier{ 'x', 1 }, grfc::action::unset),
		grfc::single_statement(false,grfc::identifier{ 'x', 2 }, grfc::action::unset)
	};

	std::vector<grfc::grafcet_timer> timer{
		grfc::grafcet_timer(5.0,3),
		grfc::grafcet_timer(2.0,4)
	};
	grfc::expression c(expr, timer);

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