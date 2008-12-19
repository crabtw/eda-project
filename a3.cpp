#include "dump_grammar.hpp"
#include "netlist_grammar.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include <cstdlib>
#include <cstring>

using namespace BOOST_SPIRIT_CLASSIC_NS;
using namespace std;

void map_values(item_map &items, value_map &values) {
    for(value_map::iterator iter = values.begin();
        iter != values.end();
        ++iter) {

        items[iter->first]->value = iter->second;
    }

    for(item_map::iterator iter = items.begin();
        iter != items.end();
        ++iter) {

        item_ptr p = iter->second;
 
        if(p->value < 0) {
            p->value = p->output.front()->value;
        }
    }
}

void print_items(item_map &items) {
    for(item_map::iterator iter = items.begin();
        iter != items.end();
        ++iter) {

        item_ptr p = iter->second;
 
        cout << p->id << "\t[val] " << p->value << " [in] ";
        if(p->input.empty()) cout << '\t';
        for(item_list::iterator in = p->input.begin();
            in != p->input.end();
            ++in) {

            cout << (*in)->id << ' ';
        }

        cout << "\t[out] ";
        for(item_list::iterator out = p->output.begin();
            out != p->output.end();
            ++out) {

            cout << (*out)->id << ' ';
        }

        cout << endl;
    }
}

string load_file(const char *path) {
    string buf;
    ifstream in(path);

    if(!in) {
        cerr << "load " << path << " failed" << endl;
        exit(-1);
    }

    while(!in.eof()) {
        string tmp;
        getline(in, tmp);
        buf.append(tmp).append(1, '\n');
    }
    in.close();

    return buf;
}

int main(int argc, char **argv) {
    string netlist, sim_dump, obs_dump;
    string out_path;

    // load files;
    for(int i = 1; i < argc; i+= 2) {
        if(strcmp(argv[i], "-netlist") == 0) {
            netlist = load_file(argv[i+1]);
        } else if(strcmp(argv[i], "-sim_dump") == 0) {
            sim_dump = load_file(argv[i+1]);
        } else if(strcmp(argv[i], "-obs_dump") == 0) {
            obs_dump = load_file(argv[i+1]);
        } else if(strcmp(argv[i], "-out")) {
            out_path = argv[i+1];
        }
    }

    netlist_grammar netlist_g;
    dump_grammar dump_g;

    item_map inputs, outputs, items;
    value_map sim_values, obs_values;

    // netlist
    parse_info<> netlist_result = parse(netlist.c_str(), netlist_g, space_p);

    inputs = netlist_g.inputs;
    netlist_g.inputs.clear();

    outputs = netlist_g.outputs;
    netlist_g.outputs.clear();

    items = netlist_g.items;
    netlist_g.items.clear();

    // sim dump
    parse_info<> sim_result = parse(sim_dump.c_str(), dump_g);
    sim_values = dump_g.values;
    dump_g.values.clear();

    // obs dump
    parse_info<> obs_result = parse(obs_dump.c_str(), dump_g);
    obs_values = dump_g.values;
    dump_g.values.clear();

    // check parsing result
    if(!(netlist_result.full && sim_result.full && obs_result.full)) {
        cerr << "parsing failed." << endl;
        exit(1);
    }

    map_values(items, sim_values);
    print_items(items);
}
