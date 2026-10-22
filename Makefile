
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

TARGET = calculator
SOURCES = main.cpp Calculator.cpp isValidator.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
