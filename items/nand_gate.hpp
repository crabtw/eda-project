#ifndef NAND_GATE
#define NAND_GATE

#include "item.hpp"

#include <boost/lambda/lambda.hpp>

struct nand_gate : item {
    bool operator()() {
        value = ~op(boost::lambda::_1 & boost::lambda::_2);
        return value;
    }
};

#endif
