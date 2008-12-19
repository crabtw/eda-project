#ifndef WIRE_ITEM
#define WIRE_ITEM

#include "item.hpp"

struct wire_item : item {
    bool operator()() {
        value = input.front()->value;
        return value;
    }
};

#endif
