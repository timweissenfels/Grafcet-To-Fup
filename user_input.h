#include <iostream>
#include <string>
#include <vector>

#include <boost/bind.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_alternative.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi_action.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/spirit/include/qi_attr.hpp>

struct trans {
	char lit;
	int num;
	boost::optional<std::string> op;
};

struct trans_expr_intern {
	trans transition;
	int according_expr;
};

struct expr {
	char lit;
	int num;
	std::string op;
	std::vector<trans_expr_intern> conditional_expr;
	bool setorunset;
};

BOOST_FUSION_ADAPT_STRUCT(
	trans,
	(char, lit),
	(int, num),
	(boost::optional<std::string>, op))

BOOST_FUSION_ADAPT_STRUCT(
	expr,
	(char, lit),
	(int, num),
	(std::string, op),
	(bool, setorunset))


static volatile int exp_trans_counter = 0;	//

void f() {									//UGLY FIX
	exp_trans_counter++;
}											//

namespace client
{
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	namespace phx = boost::phoenix;

	template <typename Iterator>
	std::pair<std::vector<expr>, bool> parse_expr(Iterator first, Iterator last)
	{
		using qi::phrase_parse;
		using ascii::space;
		exp_trans_counter = 0;

		std::vector<expr> saved_return_expressions;
		std::vector<trans_expr_intern> saved_transits_expr_intern;

		trans_expr_intern temp_trans;

		auto const identifier_input = (qi::char_("a-zA-Z") >> qi::int_);

		auto const operator_input = (qi::string("=") | qi::string(":="));
		auto const operator_conn = (qi::string("and") | qi::string("or") | qi::string("non"));

		auto const trans_input = identifier_input[phx::ref(temp_trans.transition.lit) = qi::_1, phx::ref(temp_trans.transition.num) = qi::_2] >>
			(-operator_conn | qi::attr(boost::optional<std::string>("non")))[phx::ref(temp_trans.transition.op) = qi::_1];

		auto const optional_cond = qi::char_('(') >>
			*trans_input[phx::ref(temp_trans.according_expr) = phx::ref(exp_trans_counter), phx::push_back(phx::ref(saved_transits_expr_intern), phx::ref(temp_trans))] >>
			qi::char_(')')[phx::bind(&f)];

		auto const expr_input = *(identifier_input >> operator_input >> qi::bool_ >> -optional_cond);

		bool r = phrase_parse(first, last, expr_input, space, saved_return_expressions);

		if (first != last)
			r = false;

		for (auto& tr : saved_transits_expr_intern) {
			saved_return_expressions[tr.according_expr].conditional_expr.push_back(tr);
		}

		return std::pair<std::vector<expr>, bool>{saved_return_expressions, r};
	}
}

int get_user_input() {

	std::cout << "[Expression Parser]" << std::endl;
	std::cout << "Beispiele:\n " << std::endl;

	std::string str;
	std::getline(std::cin, str);
	auto parsed = client::parse_expr(str.begin(), str.end());
	if (parsed.second)
	{
		for (auto& expr : parsed.first) {
			std::cout << '[' << expr.lit << ';' << expr.num << ';' << expr.op << ';' << std::boolalpha << expr.setorunset << ']' << std::endl;
			if (expr.conditional_expr.size() > 0) {
				for (auto& transits : expr.conditional_expr) {
					if (transits.transition.op.value().size() > 0)
						std::cout << '[' << transits.transition.lit << ';' << transits.transition.num << ';' << transits.transition.op << ']' << std::endl;
					else
						std::cout << '[' << transits.transition.lit << ';' << transits.transition.num << ']' << std::endl;
				}
			}
		}
	}
	else
	{
		std::cout << "Parsing nicht Erfolgreich\n";
	}
	return 0;
}