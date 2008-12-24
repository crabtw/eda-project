#include "dump_grammar.hpp"
#include "netlist_grammar.hpp"

#include <boost/bind.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <typeinfo>

#include <cstdlib>
#include <cstring>

using namespace BOOST_SPIRIT_CLASSIC_NS;
using namespace std;

void print_items(item_map &items) {
    for(item_map::iterator iter = items.begin();
        iter != items.end();
        ++iter) {

        item_ptr p = iter->second;
 
        cout << typeid(*p).name() << '\t' << p->id
             << "\t[val] " << p->value
             << " [in] ";
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

// breadth first traversal
template <class Function>
void bft(item_ptr &root, Function f) {
    queue<item_ptr> q;
    q.push(root);

    while(!q.empty()) {
        item_ptr item = q.front();
        item_list exit = f(item);
        q.pop();

        for(item_list::iterator child = exit.begin();
            child != exit.end();
            ++child) {

            q.push(*child);
        }
    }
}

item_list eval(item_ptr &item) {
    item->eval();
    return item->output;
}

void insert_unique(item_list *candidates, item_list *exit,
                   item_ptr &item) {
    if(
        find(candidates->begin(), candidates->end(), item)
            == candidates->end()
    ) {
        candidates->push_back(item);
        exit->push_back(item);
    }
}

item_list static_analyze(item_list *candidates, item_ptr &item) {
    // input, output, wire
    if(typeid(*item) == typeid(input_port) ||
       typeid(*item) == typeid(output_port) ||
       typeid(*item) == typeid(wire_item)) {

        return item->input;
    }

    item_list exit;

    // not, buf
    if(
        typeid(*item) == typeid(not_gate) ||
        typeid(*item) == typeid(buf_gate)
    ) {
        insert_unique(candidates, &exit, item->input.front());
        return exit;
    }

    item_list tmp;

    // and=0, nand=1, or=1, nor=0, others
    if(
        (typeid(*item) == typeid(and_gate) && item->value == 0) ||
        (typeid(*item) == typeid(nand_gate) && item->value == 1)
    ) {
        for(item_list::iterator in = item->input.begin();
            in != item->input.end();
            ++in) {

            if((*in)->value == 0) {
                tmp.push_back(*in);
            }
        }
    } else if(
        (typeid(*item) == typeid(or_gate) && item->value == 1) ||
        (typeid(*item) == typeid(nor_gate) && item->value == 0)
    ) {
        for(item_list::iterator in = item->input.begin();
            in != item->input.end();
            ++in) {

            if((*in)->value == 1) {
                tmp.push_back(*in);
            }
        }
    } else {
        for_each(
            item->input.begin(), item->input.end(),
            bind(&insert_unique, candidates, &exit, _1)
        );

        return exit;
    }

    if(tmp.size() == 1) {
        insert_unique(candidates, &exit, tmp.front());
    }

    return exit;
}

item_list dynamic_analyze(item_list *candidates, item_ptr &item) {
    item_list exit;

    for(item_list::iterator in = item->input.begin();
        in != item->input.end();
        ++in) {

        if(
            find(
                candidates->begin(), candidates->end(), *in
            ) != candidates->end()
        ) {
            candidates->remove(*in);
            exit.push_back(*in);
        }
    }

    return exit;
}

item_list brute_force(item_list *candidates, item_ptr &item) {
    item_list exit;

    if(
        typeid(*item) == typeid(input_port) ||
        typeid(*item) == typeid(output_port) ||
        typeid(*item) == typeid(wire_item)
    ) {
        exit = item->input;
    } else {
        for_each(
            item->input.begin(), item->input.end(),
            bind(&insert_unique, candidates, &exit, _1)
        );
    }

    return exit;
}

void analyze(item_map &out, value_map &obs,
             item_list &candidates, item_list &final) {
    item_map diff;

    // reduce candidates
    for(item_map::iterator item = out.begin();
        item != out.end();
        ++item) {

        if(item->second->value != obs[item->first]) {
            diff.insert(*item);
        }
    }
    // brute-force
    //diff = out;

    // static
    for(item_map::iterator item = diff.begin();
        item != diff.end();
        ++item) {

        bft(
            item->second,
            // reduce candidates
            bind(&static_analyze, &candidates, _1)
            // brute-force
            //bind(&brute_force, &candidates, _1)
        );
    }

    // dynamic
    for(item_list::iterator c = candidates.begin();
        c != candidates.end();
        ++c) {

        item_ptr &item = *c;
        item_ptr parent = item;

        if(!item->input.empty()) {
            parent = item->input.front();
        }

        parent->value = !parent->value;
        bft(item, eval);

        for(item_map::iterator o = out.begin();
            o != out.end();
            ++o) {

            if(o->second->value != obs[o->first]) {
                // reduce candidates
                bft(item, bind(dynamic_analyze, &candidates, _1));
                goto next_item;
            }
        }

        final.push_back(item);

next_item:
        parent->value = !parent->value;
        bft(item, eval);
    }
}

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

void save_file(const string &path, item_list &candidates, item_list &final) {
    ofstream out(path.c_str());

    if(!out) {
        cerr << "save " << path << " failed" << endl;
        exit(-1);
    }

    out << "Number of performing the ‘what-if’ analysis: "
        << candidates.size() << endl;
    for(item_list::iterator item = candidates.begin();
        item != candidates.end();
        ++item) {

        out << (*item)->id << endl;
    }

    out << "\nNumber of final candidates: "
        << final.size() << endl;
    for(item_list::iterator item = final.begin();
        item != final.end();
        ++item) {

        out << (*item)->id << endl;
    }

    out.close();
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
        } else if(strcmp(argv[i], "-out") == 0) {
            out_path = argv[i+1];
        }
    }

    netlist_grammar netlist_g;
    dump_grammar dump_g;

    item_map inputs, outputs, items;
    item_list candidates, final;
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
    analyze(outputs, obs_values,  candidates, final);
    save_file(out_path, candidates, final);
}
