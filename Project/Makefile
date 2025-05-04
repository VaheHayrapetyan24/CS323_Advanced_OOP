# Compiler and flags
CXX = g++
CXXFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRCS = $(wildcard *.cpp)

# Output binary
TARGET = output

# Build target
$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -o $(TARGET) $(CXXFLAGS)

# Clean build files
clean:
	rm -f $(TARGET)