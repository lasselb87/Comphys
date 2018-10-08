CPPflags = g++ -std=c++11 -O3

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
INCLUDES := -I /usr/local/Cellar/armadillo/9.100.5/include
LIB := -DARMA_DONT_USE_WRAPPER -framework Accelerate
endif

TARGETS = TwoPlanets

all: $(TARGETS)

TwoPlanets: TwoPlanets.o
	${CPPflags} -o TwoPlanets.x TwoPlanets.cpp ${LIB}
	rm -f *.o
	./TwoPlanets.x 10 0.001
	python TwoPlanets_plot.py

clean:
	rm -f *.o *.txt *.x
