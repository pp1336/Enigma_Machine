# edit this makefile so that running make compiles your enigma program

CXXFLAGS=-g -std=c++11 -Wall -pedantic

.PHONY: all

all : enigma

enigma: Main.o
	g++ $(CXXFLAGS) Main.o enigmaMachine.o rotor.o plugboard.o -o enigma

Main.o: Main.cpp enigmaMachine.o rotor.o plugboard.o
	g++ $(CXXFLAGS) -c Main.cpp -o Main.o

enigmaMachine.o: enigmaMachine.cpp
	g++ $(CXXFLAGS) -c enigmaMachine.cpp -o enigmaMachine.o

rotor.o: rotor.cpp
	g++ $(CXXFLAGS) -c rotor.cpp -o rotor.o

plugboard.o: plugboard.cpp
	g++ $(CXXFLAGS) -c plugboard.cpp -o plugboard.o

clean:
	rm -rf enigma *.o

.PHONY: clean
