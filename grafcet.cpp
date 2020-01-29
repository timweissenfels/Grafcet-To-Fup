#pragma once
#include <vector>
#include <iostream>
#include <fstream>

#include "grafcet.h"

namespace grfc {
    grafcet::grafcet(const std::vector<grfc::node> _nodes, const fup::bb _building_block) : nodes(_nodes), building_block(_building_block) {

    }

    const std::vector<grfc::node> grafcet::get_node_vec() const{
        return nodes;
    }

    void grfc::grafcet::write_as_json_tofile(std::string name) {
        jsoncons::json j;
        std::string name_outfile = name + ".json";

        std::ofstream outfile;
        outfile.open(name_outfile);

        jsoncons::json_stream_encoder encoder(outfile);

        encoder.begin_object();
        encoder.name(name);
        encode_json(this->nodes, encoder);
        encoder.end_object();
        encoder.flush();

        outfile.close();
    }

    std::ostream& operator<<(std::ostream& os, const grafcet& dt)
    {
        for (auto const& value : dt.nodes) {
            std::cout << value << std::endl;
        }

        return os;
    }
}