#pragma once

#include <vector>

#include "transition.h"
#include "expression.h"

struct node {
	int num;
	bool is_initial, is_connected_to_initial;
	std::vector<expression> expressions;
	std::vector<transition> transitions;
};