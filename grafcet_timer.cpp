#pragma once
#include <string>

#include "grafcet_timer.h"

namespace grfc {
	grafcet_timer::grafcet_timer(float _time, int number) : time(_time), ident(grfc::identifier{ 'T', number }), conn_type(grfc::conn::non)
	{
		timestr = "S5T#" + std::to_string(time);
	}
	grafcet_timer::grafcet_timer(float _time, int number,grfc::conn _conn_type) : time(_time), ident(grfc::identifier{ 'T', number }), conn_type(_conn_type)
	{
		timestr = "S5T#" + std::to_string(time);
	}
}
