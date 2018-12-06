all: main program
	
main: main.cpp directory.cpp file.h subDirectory.h memSim.h memSim.cpp
	fg++ main.cpp directory.cpp memSim.cpp -o prog

program: main.cpp directory.cpp file.h subDirectory.h memSim.h memSim.cpp
	./prog