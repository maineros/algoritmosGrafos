CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

TARGET = dijkstra.bin
SRC = dijkstra.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET) -f grafo.txt -i 1

clean:
	rm -f $(TARGET)
