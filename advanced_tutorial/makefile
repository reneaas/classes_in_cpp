all: compile execute

compile:
	g++ -o main.out $(wildcard *.cpp) -O3

execute:
	./main.out 10

plot:
	python3 plot.py test.pdf
