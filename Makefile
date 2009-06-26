
CC=CC
cc=cc
CXXFLAGS=-I. -I/workdir/release/ACE_wrappers/include -I/workdir/release/boost_1_39_0/include/boost-1_39
CFLAGs=
LDFLAGS=-L/workdir/release/ACE_wrappers/lib
LIB=-lACE

TARGET=a.out

CPPFILES=$(wildcard *.cpp)

OBJECTS=$(patsubst %.cpp, %.o, $(CPPFILES))

$(TARGET):$(OBJECTS)
	$(CC) -o $(TARGET) $(LDFLAGS) $(LIB) $(OBJECTS)

%.o:%.cpp
	$(CC) $(CXXFLAGS) -o $@ -c $< 


