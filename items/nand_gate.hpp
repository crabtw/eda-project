#ifndef NAND_GATE
#define NAND_GATE

#include "item.hpp"

#include <boost/lambda/lambda.hpp>

struct nand_gate : item {
    bool eval() {
        value = !op(boost::lambda::_1 & boost::lambda::_2);
        return value;
    }
};

#endif
