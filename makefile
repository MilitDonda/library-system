CXX = g++

CXXFLAGS = -Wall -g

TARGET = library_system

SRC = CW1.cpp

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

clean:
    rm -f $(OBJ) $(TARGET)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $<
