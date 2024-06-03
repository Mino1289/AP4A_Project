# Makefile 
# Created by KRETZ Victor
# 2023-09-15
CXX = g++
CXXFLAGS = -Wall -std=c++2a -pedantic -fpic -O3 -ggdb

SOURCES = server.cpp scheduler.cpp sensor.cpp main.cpp
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))


.o:.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: main
	./main

clean:
	rm -rf *.o main main.exe