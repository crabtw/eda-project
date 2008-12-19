all: dump_grammar.hpp netlist_grammar.hpp
	g++ -o identifyFC a3.cpp

test:
	./identifyFC -netlist test.a3/design.v -sim_dump test.a3/sim.dump \
                   -obs_dump test.a3/obs.dump -out test.a3/FC.rpt
