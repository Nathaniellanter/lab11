CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: lab11

lab11: main.cpp
	$(CXX) $(CXXFLAGS) -o lab11 main.cpp

run: lab11
	./lab11

clean:
	rm -f lab11

.PHONY: all run clean
