#include <iostream>
#include <fstream>
#include <string>

#include "transition_normal.h"
#include "transition_timer.h"
#include "transition.h"
#include "expression.h"
#include "node.h"
#include "BOOST_STRUCT_ADAPTS.h"
#include "JSONCONS_TYPE_TRAITS.h"
#include "expression_parser.h"
#include "transition_parser.h"
#include "easy_input.h"

void write_as_json_tofile(std::string name, std::vector<node> nodes) {
	jsoncons::json j;
	std::string name_outfile = name + ".json";

	std::ofstream outfile;
	outfile.open(name_outfile);

	jsoncons::json_stream_encoder encoder(outfile);
	encoder.begin_object();

	for (auto& value : nodes) {
		std::string object_name = "M120.";
		object_name.append(std::to_string(value.num));
		encoder.name(object_name);
		encode_json(value, encoder);
	}

	encoder.end_object();
	encoder.flush();
	outfile.close();
}

int main() {
	int node_count;
	std::cout << "Anzahl der Schritte: ";
	std::cin >> node_count;

	std::vector<node> nodes;

	for (int i = 0; i < node_count; i++) {
		node temp_node;
		//Get Input
		sum(var) +
			input(bool, "Ist der Schritt der Initialschritt (true/false): ") +
			input(bool, "Ist der Schritt verbunden mit dem Initialschritt (true/false): ") +
			input(std::string, "Geben Sie die Expressions ein (FORMAT): ") +
			input(std::string, "Geben Sie die Transition ein (FORMAT): ");

		//Node Number
		temp_node.num = i + 1;

		//Is Initial
		var.assign_var(0, temp_node.is_initial);

		//Is Connected to Initial
		var.assign_var(1, temp_node.is_connected_to_initial);

		std::string expr_string, trans_string;

		//Expressions
		var.assign_var(2, expr_string);

		auto parsed_expr = parser::get_expr(expr_string.begin(), expr_string.end());
		if (parsed_expr.second)
			temp_node.expressions = parsed_expr.first;

		//Transition
		var.assign_var(3, trans_string);

		auto parsed_trans = parser::get_trans(trans_string.begin(), trans_string.end());
		if (parsed_trans.second)
			temp_node.transitions = parsed_trans.first;

		nodes.push_back(temp_node);
	}

	write_as_json_tofile("Test_Json_File", nodes);
	return 0;
}