#pragma once

#include <jsoncons/json.hpp>
#include <jsoncons/encode_json.hpp>
#include <boost/optional.hpp>

#include "transition.h"
#include "expression.h"
#include "transition_normal.h"
#include "transition_timer.h"
#include "node.h"

namespace jsoncons {

	template<class Json, typename T>
	struct json_type_traits<Json, boost::optional<T>>
	{
		typedef typename Json::allocator_type allocator_type;

		static Json to_json(const boost::optional<T>& val, allocator_type alloc = allocator_type())
		{
			Json j(alloc);

			if (val)
				if(val.get() == "")
					j.try_emplace("Value", val.get());

			return j;
		}
	};
} // namespace jsoncons

JSONCONS_ALL_MEMBER_TRAITS_DECL(trans_normal, lit, num, setorunset, op, trans_num)
JSONCONS_ALL_MEMBER_TRAITS_DECL(trans_timer, time_count, unit, lit, num, trans_num, op)
JSONCONS_ALL_MEMBER_TRAITS_DECL(transition, transit_norm, transition_time)
JSONCONS_ALL_MEMBER_TRAITS_DECL(expression, lit, num, op, conditional_expr)
JSONCONS_ALL_MEMBER_TRAITS_DECL(node, num, is_initial, is_connected_to_initial, expressions, transitions)

JSONCONS_POLYMORPHIC_TRAITS_DECL(trans_normal, trans_normal)
JSONCONS_POLYMORPHIC_TRAITS_DECL(trans_timer, trans_timer)
JSONCONS_POLYMORPHIC_TRAITS_DECL(transition, transition)
JSONCONS_POLYMORPHIC_TRAITS_DECL(expression, expression)