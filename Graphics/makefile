
SRC=graphic_io.cpp graphic_structures.cpp CS430AS1.cpp
OBJS=$(subst .cpp, .o, $(SRC))

graphic_structures.o : graphic_structures.h graphic_structures.cpp
graphic_io.o: graphic_io.h graphic_io.cpp
 
clean:
	rm *.o
	rm *.xpm

graphic_structures.o: graphic_structures.cpp graphic_structures.h 
	g++ -c graphic_structures.cpp -o graphic_structures.o -std=c++11 -m64

graphic_math.o: graphic_math.cpp graphic_math.h 
	g++ -c graphic_math.cpp -o graphic_math.o -std=c++11 -m64

graphic_io.o: graphic_io.cpp graphic_io.h
	g++ -c graphic_io.cpp -o graphic_io.o -std=c++11 -m64

main.o: 3DMain.cpp
	g++ -c 3DMain.cpp -o main.o -std=c++11 -m64

build: 3DMain.cpp graphic_structures.o graphic_io.o graphic_math.o main.o
	g++ -o as6 graphic_structures.o graphic_io.o graphic_math.o main.o -std=c++11 -lstdc++ -m64
