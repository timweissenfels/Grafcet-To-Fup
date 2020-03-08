#pragma once

#include <boost/optional.hpp>

struct transition {
	boost::optional<trans_normal> transit_norm;
	boost::optional<trans_timer> transition_time;
	int according_expr;
	int trans_num;
};
