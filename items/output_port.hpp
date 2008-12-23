#ifndef OUTPUT_PORT
#define OUTPUT_PORT

#include "item.hpp"

struct output_port : item {
    bool eval() {
        value = input.front()->value;
        return value;
    }
};

#endif
