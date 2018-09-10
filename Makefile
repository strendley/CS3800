all: main program
	
main: main.cpp directory.cpp
	fg++ main.cpp directory.cpp -o prog

program: main.cpp directory.cpp
	./prog