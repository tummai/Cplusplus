#makefile for C++ program
#Tu Mai 1001595173

SRC1 = Code5_1001594173.cpp
OBJ1 = $(SRC1:.cpp=.o)
EXE = $(SRC1:.cpp=.e)

GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
CFLAGS = -g -std=c++11

all : $(EXE)

$(EXE): $(OBJ1)
	g++ $(CFLAGS) $(OBJ1) -o $(EXE) $(GTKFLAGS) 
$(OBJ1) : $(SRC1) 
	g++ -c $(CFLAGS) $(SRC1) -o $(OBJ1) $(GTKFLAGS)