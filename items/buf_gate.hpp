#ifndef BUF_GATE 
#define BUF_GATE

#include "item.hpp"

struct buf_gate : item {
    bool eval() {
        value = input.front()->value;
        return value;
    }
};

#endif
