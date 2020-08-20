all: compile execute

compile:
	c++ -o main.out main.cpp trapezoidal.cpp

execute:
	./main.out

all_alternative: compile_alternative execute

compile_alternative:
	c++ -o main.out $(wildcard *.cpp)
