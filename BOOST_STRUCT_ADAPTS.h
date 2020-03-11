#pragma once

#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional.hpp>

#include "transition.h"
#include "expression.h"
#include "transition_normal.h"
#include "transition_timer.h"

BOOST_FUSION_ADAPT_STRUCT(
	trans_normal,
	(char, lit),
	(int, num),
	(boost::optional<char>, setorunset),
	(boost::optional<std::string>, op),
	(int, trans_num)
)

BOOST_FUSION_ADAPT_STRUCT(
	trans_timer,
	(double, timer_count),
	(char, unit),
	(char, lit),
	(int, num)
)

BOOST_FUSION_ADAPT_STRUCT(
	expression,
	(char, lit),
	(int, num),
	(std::string, op)
)