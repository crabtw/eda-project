#############################################################################
# Makefile for building: identifyFC
# Generated by qmake (2.01a) (Qt 4.4.3) on: ?? ??? 25 00:03:41 2008
# Project:  eda-project.pro
# Template: app
# Command: /usr/bin/qmake -unix -o Makefile eda-project.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = 
CFLAGS        = -pipe -O2 $(DEFINES)
CXXFLAGS      = -pipe -O2 $(DEFINES)
INCPATH       = -I/usr/include -I. -I. -Iitems
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)   
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = a3.cpp \
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
OBJECTS       = a3.o \
		and_gate.o \
		buf_gate.o \
		input_port.o \
		nand_gate.o \
		nor_gate.o \
		not_gate.o \
		or_gate.o \
		output_port.o \
		wire_item.o \
		xor_gate.o
QMAKE_TARGET  = identifyFC
DESTDIR       = 
TARGET        = identifyFC

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


test:
	./identifyFC -netlist test.a3/design.v -sim_dump test.a3/sim.dump -obs_dump test.a3/obs.dump -out test.a3/FC.rpt
	./identifyFC -netlist test.a3/test01/design.v -sim_dump test.a3/test01/sim.dump -obs_dump test.a3/test01/obs.dump -out test.a3/test01/FC.rpt
	./identifyFC -netlist test.a3/test02/design.v -sim_dump test.a3/test02/sim.dump -obs_dump test.a3/test02/obs.dump -out test.a3/test02/FC.rpt
	./identifyFC -netlist test.a3/test03/design.v -sim_dump test.a3/test03/sim.dump -obs_dump test.a3/test03/obs.dump -out test.a3/test03/FC.rpt

compiler_clean: 

####### Compile

a3.o: a3.cpp dump_grammar.hpp \
		netlist_grammar.hpp \
		items/all_items.hpp \
		items/input_port.hpp \
		items/item.hpp \
		items/output_port.hpp \
		items/wire_item.hpp \
		items/and_gate.hpp \
		items/or_gate.hpp \
		items/nand_gate.hpp \
		items/nor_gate.hpp \
		items/xor_gate.hpp \
		items/not_gate.hpp \
		items/buf_gate.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o a3.o a3.cpp

and_gate.o: items/and_gate.cpp items/and_gate.hpp \
		items/item.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o and_gate.o items/and_gate.cpp

buf_gate.o: items/buf_gate.cpp items/buf_gate.hpp \
		items/item.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o buf_gate.o items/buf_gate.cpp

input_port.o: items/input_port.cpp items/input_port.hpp \
		items/item.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o input_port.o items/input_port.cpp

nand_gate.o: items/nand_gate.cpp items/nand_gate.hpp \
		items/item.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o nand_gate.o items/nand_gate.cpp

nor_gate.o: items/nor_gate.cpp items/nor_gate.hpp \
		items/item.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o nor_gate.o items/nor_gate.cpp

not_gate.o: items/not_gate.cpp items/not_gate.hpp \
		items/item.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o not_gate.o items/not_gate.cpp

or_gate.o: items/or_gate.cpp items/or_gate.hpp \
		items/item.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o or_gate.o items/or_gate.cpp

output_port.o: items/output_port.cpp items/output_port.hpp \
		items/item.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o output_port.o items/output_port.cpp

wire_item.o: items/wire_item.cpp items/wire_item.hpp \
		items/item.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o wire_item.o items/wire_item.cpp

xor_gate.o: items/xor_gate.cpp items/xor_gate.hpp \
		items/item.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o xor_gate.o items/xor_gate.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

