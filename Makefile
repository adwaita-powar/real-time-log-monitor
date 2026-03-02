
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread -Iinclude
LDFLAGS = -lncursesw

TARGET = log_engine
SRC = src/*.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)