CC = g++
CFLAGS = -Wall -std=c++17

LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = main.cpp
OUT = rocket

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)
