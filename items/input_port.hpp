#ifndef INPUT_PORT
#define INPUT_PORT

#include "item.hpp"

struct input_port : item {
    bool operator()() {
        return value;
    }
};

#endif
