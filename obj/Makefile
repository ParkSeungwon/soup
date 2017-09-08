CC = g++
OBJ = $(wildcard *.o)
EXE = $(patsubst %.x, ../%.x, $(wildcard *.x))
GTKLIB = $(shell pkg-config gtkmm-3.0 --libs)
WEBLIB = $(shell pkg-config webkit2gtk-3.0 --libs)

all : $(EXE)

../%.x : %.x $(OBJ)
	$(CC) -o $@ $< $(OBJ) -lzezeon -lrt -lpthread $(GTKLIB) $(WEBLIB) -ljsoncpp
