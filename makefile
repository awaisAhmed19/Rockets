CXX = g++
CXXFLAGS = -std=c++17 -Wall
SRC = src
OBJ = main.cpp rocket.cpp physics.cpp

all:
	$(CXX) $(CXXFLAGS) $(addprefix $(SRC)/,$(OBJ)) -o rocket -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

clean:
	rm -f rocket
