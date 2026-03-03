CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = rank
SRC = lab2.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)