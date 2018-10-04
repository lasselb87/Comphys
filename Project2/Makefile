CPPflags = g++ -std=c++11 -O3

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
INCLUDES := -I /usr/local/Cellar/armadillo/9.100.5/include
LIB := -DARMA_DONT_USE_WRAPPER -framework Accelerate
endif

ifeq ($(UNAME), Linux)
LIB := -DARMA_DONT_USE_WRAPPER -lblas -llapack
endif

TARGETS = BucklingBeam

all: $(TARGETS)

bucklingBeam: BucklingBeam.o Jacobi.o
	${CPPflags} -o BucklingBeam.x BucklingBeam.cpp Jacobi.cpp ${LIB}
	rm -f *.o
	./BucklingBeam.x

clean:
	rm -f *.o *.txt *.x

cleanResults:
	rm -f ./Results/*.txt ./Results/*.png
