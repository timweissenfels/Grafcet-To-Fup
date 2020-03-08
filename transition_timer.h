#pragma once

#include <string>

#include <boost/optional.hpp>

struct trans_timer {
	double time_count;
	char unit;
	char lit;
	int num;
	boost::optional<std::string> op;
	trans_timer(double _time_count, char _unit, char _lit, int _num, boost::optional<std::string> _op)
		: time_count(_time_count), unit(_unit), lit(_lit), num(_num), op(_op) {}
};