#ifndef NOT_GATE
#define NOT_GATE

#include "item.hpp"
#include <iostream>

struct not_gate : item {
    bool eval() {
        value = !input.front()->value;
        return value;
    }
};

#endif
