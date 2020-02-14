#pragma once
#include <string>

#include "grafcet_timer.h"

namespace grfc {
	grafcet_timer::grafcet_timer(float _time, int number) : time(_time), ident(grfc::identifier{ 'T', number })
	{
		timestr = "S5T#" + std::to_string(time);
	}
}
