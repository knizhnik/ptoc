# Constantin Knizhnik
# Moscow Software Center
# Pascal to C/C++ compiler.
#

.SUFFIXES: .cxx .c .h .o .a

default : all

#
# C/C++ compiler
#
CC = gcc
CXX = g++

#
# C/C++ flags
#
CFLAGS = -O0 -g -Wall -c
CXXFLAGS = -O0 -g -Wall -c
#CFLAGS= -fno-exceptions -O5 -g -Wall -c
#CXXFLAGS= -fno-exceptions -O5 -g -Wall -c

#
# Local packages directory
#
LOCALBASE = /usr/local

#
# Installation directory
#
PREFIX = $(LOCALBASE)

#
# Config file
#
CONFIG_FILE = $(LOCALBASE)/etc/ptoc.conf

#
# Install path
#
INSTALL_LIB_DIR = $(PREFIX)/lib
INSTALL_BIN_DIR = $(PREFIX)/bin

#
# Target.
#

BINS =	ptoc cganal 
LIBS =  libptoc.a libXbgi.a 

DEFINES = 
INCLUDES = -I.

YACC =		bison -d -p zz 
LEX =		flex -i -F -8

#
# Chose linker You prefer.
#

LD =		$(CXX)
#LDFLAGS =	-non_shared
#LDFLAGS =	-static


AR =            ar
ARFLAGS =       -ru

#
# File lists.
#

INCS =		main.h token.h token.dpp nmtbl.h bring.h tpexpr.h trnod.h util.h

SRCS =		trnod.cxx nmtbl.cxx bring.cxx tpexpr.cxx util.cxx main.cxx parser.cxx lex.cxx token.cxx dprintf.cxx 

LIB_SRCS =      set.c paslib.c io.c

OBJS =		$(SRCS:.cxx=.o)

LIB_OBJS =      $(LIB_SRCS:.c=.o)

#
# Default way in which source files should be compiled.
#

.cxx.o : 
		$(CXX) $(CXXFLAGS) $(DEFINES) $(INCLUDES) -o $@ -c $<

.c.o : 
		$(CC) $(CXXFLAGS) $(DEFINES) $(INCLUDES) -o $@ -c $<

#
# Custom targets.
#


$(OBJS) : $(INCS)

parser.cxx parser.h : parser.y 
		$(YACC) parser.y 
		mv parser.tab.c parser.cxx
		mv parser.tab.h parser.h

lex.cxx : lex.l 
		$(LEX) lex.l
		mv lex.yy.c lex.cxx

lex.o: lex.cxx token.h token.dpp
set.o: set.h ptoc.h 
array.o: array.h ptoc.h 
paslib.o: paslib.h ptoc.h
io.o: io.h ptoc.h 
analyse.o: analyse.cxx main.h

libptoc.a: $(LIB_OBJS)
	rm -f $@
	$(AR) $(ARFLAGS) $@ $(LIB_OBJS)
	ranlib $@

cganal : analyse.o
	$(LD) $(LDFLAGS) -o $@ analyse.o

ptoc : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

libXbgi.a: 
	(cd Xbgi; make)

all : $(BINS) $(LIBS) 

clean:
	rm -f $(BINS) *.a a.out *.exe *.pdb *.lib *.tgz *.zip *.o lex.yy.c \
		parser.tab.* WinBGI/*.pdb yy.log core y.output parser.output *~
	(cd examples; make clean)
	(cd Xbgi; make clean)

tgz: clean
	(cd ..; tar cvzf ptoc.tgz ptoc)

copytgz: tgz
	mcopy -o ../ptoc.tgz a:

install: $(BINS) $(LIBS)
	cp $(BINS) $(INSTALL_BIN_DIR)	
	cp $(LIBS) $(INSTALL_LIB_DIR)
