#ifndef XOR_GATE
#define XOR_GATE

#include "item.hpp"

#include <boost/lambda/lambda.hpp>

struct xor_gate : item {
    bool eval() {
        value = op(boost::lambda::_1 ^ boost::lambda::_2);
        return value;
    }
};

#endif
