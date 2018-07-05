SRC=GameState.cpp Move.cpp Coordinates.cpp
OBJS=GameState.o Coordinates.o Move.o test.o

all: $(OBJS)
	g++ -o test $(OBJS)

test.o: test.cpp GameState.h Coordinates.h Move.h
	g++ -c -g test.cpp

game-state.o: GameState.cpp
	g++ -c GameState.cpp

coordinates.o: Coordinates.cpp
	g++ -c Coordinates.cpp

move.o: Move.cpp
	g++ -c Move.cpp

clean:
	rm *.o
