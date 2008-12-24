#include "not_gate.hpp"

void not_gate::eval() {
    value = !input.front()->value;
}
