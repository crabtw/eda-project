#ifndef NOT_GATE
#define NOT_GATE

#include "item.hpp"

struct not_gate : item {
    bool operator()() {
        value = ~input.front()->value;
        return value;
    }
};

#endif
