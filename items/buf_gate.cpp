#include "buf_gate.hpp"

void buf_gate::eval() {
    value = input.front()->value;
}
