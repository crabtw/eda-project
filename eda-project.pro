######################################################################
# Automatically generated by qmake (2.01a) ?? ??? 24 20:42:35 2008
######################################################################

TEMPLATE = app
TARGET = identifyFC
DEPENDPATH = . items
INCLUDEPATH = . items

CONFIG =

# test target
defineReplace(inputFiles) {
    dir = $$ARGS
    files = -netlist $$dir/design.v \
            -sim_dump $$dir/sim.dump \
            -obs_dump $$dir/obs.dump \
            -out $$dir/FC.rpt

    return($$files)
}

testDirs = test.a3 \
           test.a3/test01 \
           test.a3/test02 \
           test.a3/test03 \
           test.a3/test04

for(dir, testDirs) {
    cmd += ./$$TARGET $$inputFiles($$dir);
}

test.target = test
test.commands = $$cmd

QMAKE_EXTRA_TARGETS += test

# Input
HEADERS = dump_grammar.hpp \
           netlist_grammar.hpp \
           items/all_items.hpp \
           items/and_gate.hpp \
           items/buf_gate.hpp \
           items/input_port.hpp \
           items/item.hpp \
           items/nand_gate.hpp \
           items/nor_gate.hpp \
           items/not_gate.hpp \
           items/or_gate.hpp \
           items/output_port.hpp \
           items/wire_item.hpp \
           items/xor_gate.hpp
SOURCES = a3.cpp \
           items/and_gate.cpp \
           items/buf_gate.cpp \
           items/input_port.cpp \
           items/nand_gate.cpp \
           items/nor_gate.cpp \
           items/not_gate.cpp \
           items/or_gate.cpp \
           items/output_port.cpp \
           items/wire_item.cpp \
           items/xor_gate.cpp
