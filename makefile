CXX = g++
DEBUG = -Wall -g3 -DDEBUG
RELEASE = -O2 -DRELEASE
CXXFLAGS = -std=c++11 $(DEBUG)
LIB = board.o ai.o

all: main.cpp $(LIB)
	$(CXX) main.cpp $(LIB) -o main $(CXXFLAGS)

board.o: board.h board.cpp
	$(CXX) -c board.cpp -o board.o $(CXXFLAGS)

.o: ai.h ai.cpp
	$(CXX) -c ai.cpp -o ai.o $(CXXFLAGS)

clean:
	rm -rf main $(LIB)
