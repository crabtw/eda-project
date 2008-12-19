#ifndef NETLIST_GRAMMAR
#define NETLIST_GRAMMAR

#include "items/all_items.hpp"

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_confix.hpp>
#include <boost/spirit/include/classic_distinct.hpp>
#include <boost/spirit/include/classic_lists.hpp>
#include <boost/spirit/include/classic_symbols.hpp>

#include <boost/bind.hpp>

#include <map>
#include <string>
#include <utility>

namespace spirit = BOOST_SPIRIT_CLASSIC_NS;

typedef std::map<std::string, item_ptr> item_map;

enum link_type {
    input_type, output_type, wire_type
};

enum gate_type {
    and_type, or_type, nand_type, nor_type,
    xor_type, not_type, buf_type
};


namespace {
    spirit::distinct_directive<> keyword_d("a-zA-Z0-9");

    void set_link(spirit::symbols<link_type> *table, link_type *type,
                  const char *str, const char *end) {
        std::string s(str, end);
        *type = *spirit::find(*table, s.c_str());
    }

    void set_gate(spirit::symbols<gate_type> *table, gate_type *type,
                  const char *str, const char *end) {
        std::string s(str, end);
        *type = *spirit::find(*table, s.c_str());
    }

    void create_link(link_type *type, std::list<std::string> *ids,
                     item_map *inputs, item_map *outputs, item_map *items,
                     const char *, const char *) {
        for(std::list<std::string>::iterator iter = ids->begin();
            iter != ids->end();
            ++iter) {

            item_ptr ptr;

            switch(*type) {
            case input_type:
                ptr.reset(new input_port);
                inputs->insert(std::make_pair(*iter, ptr));
                break;
            case output_type:
                ptr.reset(new output_port);
                outputs->insert(std::make_pair(*iter, ptr));
                break;
            case wire_type:
                ptr.reset(new wire_item);
                break;
            }

            ptr->id = *iter;
            items->insert(std::make_pair(*iter, ptr));
        }
    }

    void create_gate(gate_type *type, item_ptr *gate,
                     item_map *items,
                     const char *str, const char *end) {
        std::string s(str, end);
        item_ptr ptr;

        switch(*type) {
        case and_type:
            ptr.reset(new and_gate);
            break;
        case or_type:
            ptr.reset(new or_gate);
            break;
        case nand_type:
            ptr.reset(new nand_gate);
            break;
        case nor_type:
            ptr.reset(new nor_gate);
            break;
        case xor_type:
            ptr.reset(new xor_gate);
            break;
        case not_type:
            ptr.reset(new not_gate);
            break;
        case buf_type:
            ptr.reset(new buf_gate);
            break;
        }

        ptr->id = s;
        items->insert(std::make_pair(s, ptr));

        *gate = ptr;
    }

    void connect(std::list<std::string> *ids, item_ptr *gate,
                 item_map *items,
                 const char *, const char *) {
        std::list<std::string>::iterator iter = ids->begin();

        (*gate)->output.push_back((*items)[*(++iter)]);
        (*items)[*iter]->input.push_back(*gate);

        for(++iter;
            iter != ids->end();
            ++iter) {

            (*gate)->input.push_back((*items)[*iter]);
            (*items)[*iter]->output.push_back(*gate);
        }
    }

    void add_id(std::list<std::string> *ids,
                const char *str, const char *end) {
        std::string s(str, end);
        ids->push_back(s);
    }

    void clear_ids(std::list<std::string> *ids,
                   char) {
        ids->clear();
    }
}

struct netlist_grammar : spirit::grammar<netlist_grammar> {
    template <typename ScannerT>
    struct definition {
        definition(netlist_grammar const& self) {
            using namespace std;
            using namespace spirit;

            item_map &inputs = const_cast<item_map &>(self.inputs);
            item_map &outputs = const_cast<item_map &>(self.outputs);
            item_map &items = const_cast<item_map &>(self.items);

            entry
                =   *comment
                    >> module_dec
                    >> +link_dec
                    >> +gate_dec
                    >> endmodule
                    >> end_p
                ;

            // declaration
            module_dec
                =   keyword_d["module"]
                    >> id
                    >> id_tuple
                    >> separator
                ;
            link_dec
                =   keyword_d[link_keywords]
                    [
                        bind
                        (
                            &set_link,
                            &link_keywords, &cur_link_type,
                            _1, _2
                        )
                    ]
                    >> id_list
                    [
                        bind
                        (
                            &create_link,
                            &cur_link_type, &ids,
                            &inputs, &outputs, &items,
                            _1, _2
                        )
                    ]
                    >> separator
                ;
            gate_dec
                =   keyword_d[gate_keywords]
                    [
                        bind
                        (
                            &set_gate,
                            &gate_keywords, &cur_gate_type,
                            _1, _2
                        )
                    ]
                    >> id
                    [
                        bind
                        (
                            &create_gate,
                            &cur_gate_type, &cur_gate,
                            &items,
                            _1, _2
                        )
                    ]
                    >> id_tuple
                    [
                        bind
                        (
                            &connect,
                            &ids, &cur_gate,
                            &items,
                            _1, _2
                        )
                    ]
                    >> separator
                ;
            endmodule
                =   keyword_d["endmodule"]
                ;

            // others
            id_tuple
                =   confix_p('(', id_list, ')')
                ;
            id_list
                =   list_p(id, ',')
                ;
            id
                =   lexeme_d
                    [
                        alpha_p
                        >> *( alnum_p
                            | ch_p('_')
                            )
                    ]
                    [
                        bind
                        (
                            &add_id,
                            &ids,
                            _1, _2
                        )
                    ]
                ;
            separator
                =   ch_p(';')
                    [
                        bind
                        (
                            &clear_ids,
                            &ids,
                            _1
                        )
                    ]
                ;
            comment
                =   lexeme_d
                    [
                        comment_p("//")
                    |   comment_p("/*", "*/")
                    ]
                ;

            // keywords
            link_keywords.add
                ("input", input_type)
                ("output", output_type)
                ("wire", wire_type)
                ;
            gate_keywords.add
                ("and", and_type)
                ("or", or_type)
                ("nand", nand_type)
                ("nor", nor_type)
                ("xor", xor_type)
                ("not", not_type)
                ("buf", buf_type)
                ;
        }

        spirit::rule<ScannerT> entry;
        spirit::rule<ScannerT> module_dec, link_dec, gate_dec, endmodule;
        spirit::rule<ScannerT> id_tuple, id_list, id, separator, comment;

        spirit::symbols<link_type> link_keywords;
        spirit::symbols<gate_type> gate_keywords;

        spirit::rule<ScannerT> const& start() const {
            return entry;
        }

    private:
        link_type cur_link_type;
        gate_type cur_gate_type;

        std::list<std::string> ids;
        item_ptr cur_gate;
    };


    item_map inputs;
    item_map outputs;
    item_map items;
};

#endif
