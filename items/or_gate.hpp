#ifndef OR_GATE
#define OR_GATE

#include "item.hpp"

#include <boost/lambda/lambda.hpp>

struct or_gate : item {
    bool eval() {
        value = op(boost::lambda::_1 | boost::lambda::_2);
        return value;
    }
};

#endif
