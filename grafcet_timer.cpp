#pragma once
#include <string>

#include "grafcet_timer.h"

namespace grfc {
	grafcet_timer::grafcet_timer(float _time = 0, std::string _name = "T1", fup::bb _building_block) : time(_time), name(_name), building_block(_building_block)
	{

	}
}
