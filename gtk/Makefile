CFLAG = -g -c -std=c++14 -fmax-errors=1
INCLUDE = -I../ -I../src
GTKCFLAG = $(shell pkg-config gtkmm-3.0 webkit2gtk-3.0 gtksourceviewmm-3.0 --cflags) #-I$(ROOT)
WEBFLAG = $(shell pkg-config webkit2gtk-3.0 --cflags)
SOURCEVIEW = $(shell pkg-config gtksourceviewmm-3.0 --cflags)

CC = g++
OBJ = $(patsubst %.cc, ../obj/%.o, $(wildcard *.cc))
MAIN_OBJ = $(patsubst %.cpp, ../obj/%.x, $(wildcard *.cpp))

all : $(OBJ) $(MAIN_OBJ)

../obj/%.o : %.cc 
	$(CC) $(GTKCFLAG) $(INCLUDE) $(CFLAG) $< -o $@

../obj/%.x : %.cpp
	$(CC) $(GTKCFLAG) $(INCLUDE) $(CFLAG) $< -o $@

