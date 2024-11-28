CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++20 -Wold-style-cast -g
SRC= src/main.cpp
OBJ= 

all : $(addprefix src/,$(OBJ))
	$(CXX) $(SRC) $^ -o main

clean :
	rm -f $(addprefix src/,$(OBJ))
	rm main
