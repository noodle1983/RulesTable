
CC=CC
cc=cc
CXXFLAGS=-I. -I/workdir/release/boost_1_39_0/include/boost-1_39
CFLAGs=
LDFLAGS=
LIB=

TARGET=a.out

CPPFILES=$(wildcard *.cpp)

OBJECTS=$(patsubst %.cpp, %.o, $(CPPFILES))

$(TARGET):$(OBJECTS)
	$(CC) -o $(TARGET) $(LDFLAGS) $(LIB) $(OBJECTS)

%.o:%.cpp
	$(CC) $(CXXFLAGS) -o $@ -c $< 

clean:
	rm -rf $(TARGET)
	rm -rf *.o
