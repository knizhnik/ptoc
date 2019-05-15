#
# Compilers
#
CC = gcc
CXX = g++
CGANAL = ../cganal
PTOC = ../ptoc

#
# Include files and libraries
#
PTOC_INC = -I..
PTOC_LIB = ../libptoc.a
BGI_LIB = ../libXbgi.a
GRAPH_LIB = -L/usr/X11R6/lib -lX11
MATH_LIB = -lm

EXE = hello_c hello_cxx impact war2 trinor tpascal set_c set_cxx lister polut2 vibrkinp vibrtabl bgidemo

all: convert executable

convert: hello.c hello.cxx impact.cxx war2.cxx test.c test.cxx polut2.cxx \
rename.cxx tpascal.cxx trinor.cxx lister.cxx vibrkinp.cxx vibrtabl.cxx bgidemo.cxx

executable: $(EXE)

# Hello world

hello.c: hello.pas
	$(PTOC) -c -in hello.pas 

hello.cxx: hello.pas
	$(PTOC) -in hello.pas

hello_c: hello.c
	$(CC) $(PTOC_INC) -o hello_c hello.c $(PTOC_LIB)

hello_cxx: hello.cxx
	$(CXX) $(PTOC_INC) -o hello_cxx hello.cxx $(PTOC_LIB)

#----------------------------------------------------------------
# Graphic example: BGIDEMO
#----------------------------------------------------------------
bgidemo.cxx: bgidemo.pas
	$(PTOC) -turbo -preserve -analyze -in bgidemo.pas

bgidemo: bgidemo.cxx
	$(CXX) $(PTOC_INC) -DTURBO_PASCAL -funsigned-char -o bgidemo bgidemo.cxx $(PTOC_LIB) $(BGI_LIB) $(GRAPH_LIB) $(MATH_LIB)

#----------------------------------------------------------------
# Some numeric programs for Turbo Pascal
#----------------------------------------------------------------

# Examples with BGI
vibrtabl.cxx: vibrtabl.pas
	$(PTOC) -turbo -in vibrtabl.pas

vibrtabl: vibrtabl.cxx
	$(CXX) $(PTOC_INC) -DTURBO_PASCAL -o vibrtabl vibrtabl.cxx $(PTOC_LIB) $(BGI_LIB) $(GRAPH_LIB) $(MATH_LIB)


vibrkinp.cxx: vibrkinp.pas
	$(PTOC) -turbo -in vibrkinp.pas

vibrkinp: vibrkinp.cxx
	$(CXX) $(PTOC_INC) -DTURBO_PASCAL -o vibrkinp vibrkinp.cxx $(PTOC_LIB) $(BGI_LIB) $(GRAPH_LIB) $(MATH_LIB)


polut2.cxx: polut2.pas
	$(PTOC) -turbo -in polut2.pas

polut2: polut2.cxx
	$(CXX) $(PTOC_INC) -DTURBO_PASCAL -o polut2 polut2.cxx $(PTOC_LIB) $(BGI_LIB) $(GRAPH_LIB) $(MATH_LIB)


impact.cxx: impact.pas
	$(PTOC) -turbo -in impact.pas

impact: impact.cxx
	$(CXX) $(PTOC_INC) -DTURBO_PASCAL -o impact impact.cxx $(PTOC_LIB) $(MATH_LIB)

trinor.cxx: trinor.pas
	$(PTOC) -turbo -in trinor.pas

trinor: trinor.cxx
	$(CXX) $(PTOC_INC) -DTURBO_PASCAL -o trinor trinor.cxx $(PTOC_LIB) $(MATH_LIB)


war2.cxx: war2.pas
	$(PTOC) -turbo -in war2.pas

war2: war2.cxx
	$(CXX) $(PTOC_INC) -DTURBO_PASCAL -o war2 war2.cxx $(PTOC_LIB) $(MATH_LIB)
# This program reads data from files war2.txt, random.txt, coord.txt
# and produce file xy2.txt. Your can compare this file with xy2orig.txt
# produced by original Pascal program. 

#-------------------------------------------------------------------
# File from examples to Borland Pascal.
#-------------------------------------------------------------------

lister.cxx: lister.pas
	$(PTOC) -turbo -init -in lister.pas

printer.cxx: printer.pas
	$(PTOC) -turbo -init -in printer.pas

lister: lister.cxx printer.cxx
	$(CXX) $(PTOC_INC) -DTURBO_PASCAL -o lister lister.cxx printer.cxx $(PTOC_LIB) 

#-------------------------------------------------------------------
# Some tests for converter. This programms produce dummy output.
#-------------------------------------------------------------------

test.c: test.pas
	rm -f call.grp
	$(PTOC) -c -analyze -smallenum -intset -in test.pas
	$(CGANAL)	
	$(PTOC) -c -analyze -smallenum -intset -in test.pas 
# It is neccessary to run converter twice.
# At first phase call graph of functions is constructed and
# at second phase correct code is generated.

test.cxx: test.pas
	rm -f call.grp
	$(PTOC) -analyze -in test.pas
	$(CGANAL)
	$(PTOC) -analyze -in test.pas

rename.cxx: rename.pas
	$(PTOC) -in rename.pas

set.cxx: set.pas
	$(PTOC) -in set.pas

set.c: set.pas
	$(PTOC) -c -intset -in set.pas

set_cxx: set.cxx
	$(CXX) $(PTOC_INC) -o set_cxx set.cxx $(PTOC_LIB)

set_c: set.c
	$(CC) $(PTOC_INC) -o set_c set.c $(PTOC_LIB)

# Test for Turbo Pascal

tpascal.cxx: tpascal.pas
	$(PTOC) -turbo -cstring -in tpascal.pas

tpascal: tpascal.cxx
	$(CXX) $(PTOC_INC) -o tpascal -DTURBO_PASCAL tpascal.cxx $(PTOC_LIB)


#
# Erase intermediate files after generating binaries
#

clean:
	rm -f $(EXE) $(convert) *~ *.o *.core call.grp recur.prc \
	hello.c hello.cxx impact.cxx war2.cxx trinor.cxx tpascal.cxx \
	set.c set.cxx lister.cxx polut2.cxx vibrkinp.cxx vibrtabl.cxx \
	bgidemo.cxx printer.cxx printer.h

