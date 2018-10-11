CPPflags = g++ -O3

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
INCLUDES := -I /usr/local/Cellar/armadillo/9.100.5/include
LIB := -DARMA_DONT_USE_WRAPPER -framework Accelerate
endif



TwoPlanets: TwoPlanets.o
	${CPPflags} -o TwoPlanets.x TwoPlanets.cpp ${LIB}
	rm -f *.o
	./TwoPlanets.x 10 0.001
	python TwoPlanets_plot.py

main: main.o solver.o planets.o
	${CPPflags} -o main.x main.cpp solver.cpp planets.cpp ${LIB}
	rm -f *.o
	./main.x 100 0.001
	python solarsystemPlot.py

test: test.o
	${CPPflags} -o test.x test.cpp ${LIB}
	rm -f *.o
	./test.x


clean:
	rm -f *.o *.txt *.x
