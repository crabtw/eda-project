#include "output_port.hpp"

void output_port::eval() {
    value = input.front()->value;
}
