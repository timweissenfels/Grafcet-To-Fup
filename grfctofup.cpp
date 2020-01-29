#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <jsoncons/json.hpp>
#include <jsoncons/encode_decode_json.hpp>

#include "enum_identifier.h"
#include "single_statement.h"
#include "transition.h"
#include "expression.h"
#include "node.h"
#include "grafcet.h"
#include "grafcet_timer.h"



int main()
{
    std::vector<grfc::single_statement> x = { 
        grfc::single_statement(false, grfc::identifier{'S',1},grfc::conn::dot), grfc::single_statement(false,grfc::identifier{'S',2},grfc::conn::plus), grfc::single_statement(true,grfc::identifier{'S',3})
    };
    
    grfc::transition transition_test(x,true);
    
    grfc::expression c(std::vector<std::pair<const grfc::identifier, const grfc::action>> { 
        std::pair<const grfc::identifier, const grfc::action>{grfc::identifier{'x', 1},grfc::action::unset},
        std::pair<const grfc::identifier, const grfc::action>{grfc::identifier{'x', 2}, grfc::action::unset}      
    });


    auto vf = std::vector<grfc::node>{ grfc::node(true, 1, transition_test, c),grfc::node(false, 1, transition_test, c) };
    vf.push_back(grfc::node(false, 2, transition_test, c, std::pair<bool, std::shared_ptr<grfc::node>>{true, std::make_shared<grfc::node>(vf[0])}));

    grfc::grafcet first_grfc(vf,fup::bb::fc1);

    std::cout << first_grfc;
}