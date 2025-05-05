CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRC = src/main.cpp src/game.cpp
OBJ = $(SRC:.cpp=.o)

snake: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) snake