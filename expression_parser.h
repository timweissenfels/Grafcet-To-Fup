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
#include "expression.h"

static volatile int exp_trans_counter = 0;
static volatile int trans_order_counter = 0;


void exp_trans_counter_func() {
	exp_trans_counter++;
}

void trans_order_counter_func() {
	trans_order_counter++;
}

namespace parser
{
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	namespace phx = boost::phoenix;

	template <typename Iterator>
	std::pair<std::vector<expression>, bool> get_expr(Iterator first, Iterator last)
	{
		using qi::phrase_parse;
		using ascii::space;
		exp_trans_counter = 0;
		trans_order_counter = 0;

		std::vector<expression> saved_return_expressions;
		std::vector<transition> saved_transits_expr_intern;

		transition temp_trans;

		auto const identifier_input = (qi::char_("a-zA-Z") >> qi::int_);

		auto const operator_input = (qi::string("=") | qi::string(":="));
		auto const operator_conn = (qi::string("and") | qi::string("or"));

		auto const timer_input = (qi::double_ >> qi::char_('s') >> qi::char_("/") >> identifier_input >> (-operator_conn | qi::attr(boost::optional<std::string>())))
			[phx::ref(temp_trans.transition_time) = phx::construct<trans_timer>(qi::_1, qi::_2, qi::_4, qi::_5, qi::_6, phx::ref(trans_order_counter)), phx::bind(&trans_order_counter_func)];

		auto const trans_input = (((-qi::char_('!') | qi::attr(boost::optional<char>())) >> identifier_input >> (-operator_conn | qi::attr(boost::optional<std::string>())))
			[phx::ref(temp_trans.transit_norm) = phx::construct<trans_normal>(qi::_1, qi::_2, qi::_3, qi::_4, phx::ref(trans_order_counter)), phx::bind(&trans_order_counter_func)] | timer_input);

		auto const optional_cond = qi::char_('(') >>
			*trans_input[phx::ref(temp_trans.according_expr) = phx::ref(exp_trans_counter), phx::push_back(phx::ref(saved_transits_expr_intern), phx::ref(temp_trans))] >>
			qi::char_(')')[phx::bind(&exp_trans_counter_func)];

		auto const expr_input = *(identifier_input >> operator_input >> qi::bool_ >> -optional_cond);

		bool r = phrase_parse(first, last, expr_input, space, saved_return_expressions);

		if (first != last)
			r = false;

		for (auto& tr : saved_transits_expr_intern) {
			saved_return_expressions[tr.according_expr].conditional_expr.push_back(tr);
		}

		return std::pair<std::vector<expression>, bool> {saved_return_expressions, r};
	}
}