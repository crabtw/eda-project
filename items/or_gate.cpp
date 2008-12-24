#include "or_gate.hpp"

#include <boost/lambda/lambda.hpp>

using namespace boost::lambda;

void or_gate::eval() {
    value = op(_1 | _2);
}
