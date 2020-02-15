#pragma once

namespace fup {
    //bb = building block
    enum bb { fc1 = 1, fc2 = 2, fc3 = 3 };
}

namespace grfc {

    //CONN and ACTION ENUMS
    //dot == and ; plus == or
    enum class conn : const char { non = ' ', dot = 'o', plus = '+' };
    enum class action : const char { set = ' ', unset = '!', timer='t', equal='=', rising_edge = 'r', falling_edge = 'f' };

    //IDENTIFIER STRUCT
    struct identifier final {
        const char literal;
        const int number;
    };
}
