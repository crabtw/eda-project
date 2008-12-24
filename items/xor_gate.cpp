#include "xor_gate.hpp"

#include <boost/lambda/lambda.hpp>

using namespace boost::lambda;

void xor_gate::eval() {
    value = op(_1 ^ _2);
}
