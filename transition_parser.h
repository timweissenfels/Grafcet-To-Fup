#pragma once

#include <vector>

#include <boost/bind.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/optional.hpp>
#include <boost/phoenix/object/construct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_alternative.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi_action.hpp>
#include <boost/spirit/include/qi_as.hpp>

#include "transition.h"
#include "transition_normal.h"
#include "transition_timer.h"

namespace parser
{
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	namespace phx = boost::phoenix;

	template <typename Iterator>
	std::pair<std::vector<transition>, bool> get_trans(Iterator first, Iterator last)
	{
		using qi::phrase_parse;
		using ascii::space;
		trans_order_counter = 0;

		std::vector<transition> transitions;

		transition temp_trans;

		auto const identifier_input = (qi::char_("a-zA-Z") >> qi::int_);

		auto const operator_conn = (qi::string("and") | qi::string("or"));

		auto const timer_input = (qi::double_ >> qi::char_('s') >> qi::char_("/") >> identifier_input >> (-operator_conn | qi::attr(boost::optional<std::string>())))
			[phx::ref(temp_trans.transition_time) = phx::construct<trans_timer>(qi::_1, qi::_2, qi::_4, qi::_5, qi::_6), phx::ref(temp_trans.trans_num) = phx::ref(trans_order_counter), phx::bind(&trans_order_counter_func)];

		auto const trans_input = (((-qi::char_('!') | qi::attr(boost::optional<char>())) >> identifier_input >> (-operator_conn | qi::attr(boost::optional<std::string>())))
			[phx::ref(temp_trans.transit_norm) = phx::construct<trans_normal>(qi::_1, qi::_2, qi::_3, qi::_4), phx::ref(temp_trans.trans_num) = phx::ref(trans_order_counter), phx::bind(&trans_order_counter_func)] | timer_input);

		bool r = phrase_parse(first, last,
			*trans_input[phx::ref(temp_trans.according_expr) = 0, phx::push_back(phx::ref(transitions), phx::ref(temp_trans))], space);

		if (first != last)
			r = false;

		return std::pair<std::vector<transition>, bool> {transitions, r};
	}
}