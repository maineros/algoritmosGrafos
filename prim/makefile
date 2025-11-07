CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

TARGET = prim.bin
SRC = prim.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET) -f grafo.txt -i 0

clean:
	rm -f $(TARGET)
