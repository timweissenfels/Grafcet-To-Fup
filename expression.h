#pragma once

#include <vector>
#include <string>

#include "transition.h"

struct expression {
	char lit;
	int num;
	std::string op;
	std::vector<transition> conditional_expr;
};