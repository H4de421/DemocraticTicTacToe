CXX=g++
CXXFLAGS=
#-Wall -Wextra -Werror -std=c++20 -Wold-style-cast -g
SRC= src/main.cpp
OBJ= Board.o Game.o AI/Automaton.o	
all : $(addprefix src/,$(OBJ))
	$(CXX) $(SRC) $^ -o main

debug :  $(addprefix src/,$(OBJ))
	$(CXX) -g $(SRC) $^ -o main

clean :
	rm -f $(addprefix src/,$(OBJ))
	rm -f main