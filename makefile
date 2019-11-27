OBJS=cmd.o main.o
CXXFLAGS=-O2 -std=c++11
GOOGLE_TEST_LIB = gtest
GOOGLE_TEST_INCLUDE = /usr/local/include

G++_FLAGS = -c -Wall -I $(GOOGLE_TEST_INCLUDE)
LD_FLAGS = -L /usr/local/lib -l $(GOOGLE_TEST_LIB) -l pthread
OBJECTS = cmdtest.o
TARGET = cmdtest

terminal: $(OBJS)
	g++ -o terminal $(OBJS)
main.o: main.cpp
	g++ -c main.cpp $(CXXFLAGS)
cmd.o: cmd.cpp
	g++ -c cmd.cpp $(CXXFLAGS)
cmdtest.o: cmdtest.cpp
	g++ $(G++_FLAGS) $<
$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LD_FLAGS)
clean:
	rm -f *.o
