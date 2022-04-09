
CC=g++
cc=gcc
CXXFLAGS=-g -O0 -I. -std=c++11
CFLAGs=
LDFLAGS=
LIB=

CPPFILES=$(wildcard *.cpp)

OBJECTS=$(patsubst %.cpp, %.o, $(CPPFILES))

TARGET=$(patsubst %.cpp, %.out, $(CPPFILES))

%.out:%.cpp
	$(CC) $(CXXFLAGS) -o $@  $< 

all:$(TARGET)

depend:
	$(CC) $(CXXFLAGS) -MM test.cpp 

clean:
	rm -rf $(TARGET)
	rm -rf *.o
