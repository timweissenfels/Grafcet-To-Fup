#pragma once

#include <string>

#include <boost/optional.hpp>

struct trans_normal {
	char lit;
	int num;
	boost::optional<char> setorunset;
	boost::optional<std::string> op;
	int trans_num;
	trans_normal(boost::optional<char> _setorunset, char _lit, int _num, boost::optional<std::string> _op, int _trans_num)
		: lit(_lit), num(_num), op(_op), trans_num(_trans_num), setorunset(_setorunset) {}
};