all: main program
	
main: main.cpp attributes.cpp attributes.h dir.cpp dir.h file.h permissions.cpp permissions.h shellEmu.cpp shellEmu.h
	fg++ main.cpp attributes.cpp dir.cpp permissions.cpp shellEmu.cpp -o prog

program: main.cpp attributes.cpp attributes.h dir.cpp dir.h file.h permissions.cpp permissions.h shellEmu.cpp shellEmu.h
	./prog