CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -framework OpenGL -framework GLUT -I/opt/homebrew/include -L/opt/homebrew/lib -lfreeimage
SOURCES = PACMAN.cpp
TARGET = Source

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)