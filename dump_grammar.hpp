#ifndef DUMP_GRAMMAR
#define DUMP_GRAMMAR

#include <boost/spirit/include/classic_core.hpp>

#include <boost/bind.hpp>

#include <map>
#include <string>
#include <utility>

namespace spirit = BOOST_SPIRIT_CLASSIC_NS;

typedef std::map<std::string, int> value_map;

namespace {
   void set_id(std::string *id, 
               const char *str, const char *end) {
       std::string s(str, end);
       *id = s;
   }

   void insert(std::string *id, value_map *values,
               int val) {
        values->insert(make_pair(*id, val));
   }
}

struct dump_grammar : spirit::grammar<dump_grammar> {
    template <typename ScannerT>
    struct definition {
        definition(dump_grammar const& self) {
            using namespace spirit;
            using namespace std;

            value_map &val = const_cast<value_map &>(self.values);

            entry
                =   +assignment
                    >> *space_p
                ;
            assignment
                =   id
                    [
                        bind
                        (
                            &set_id,
                            &cur_id,
                            _1, _2
                        )
                    ]
                    >> *ch_p(' ')
                    >> ch_p('=')
                    >> *ch_p(' ')
                    >> bin_p
                        [
                            bind
                            (
                                &insert,
                                &cur_id, &val,
                                _1
                            )
                        ]
                    >> eol_p
                ;
            id
                =   lexeme_d
                    [
                        alpha_p
                        >> *( alnum_p
                            | ch_p('_')
                            )
                    ]
                ;
        }

        spirit::rule<ScannerT> entry;
        spirit::rule<ScannerT> assignment, id;

        spirit::rule<ScannerT> const& start() const {
            return entry;
        }

    private:
        std::string cur_id;
    };

    value_map values;
};

#endif
