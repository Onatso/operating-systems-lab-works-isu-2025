# Compiler and flags
CXX      = g++
CXXFLAGS = -Wall -Wextra -I./src -std=c++17
LDFLAGS  = 
TARGET   = bin/program

# Source files and objects
SRC_DIR = src
SRC     = $(wildcard $(SRC_DIR)/*.cpp)
OBJ     = $(patsubst $(SRC_DIR)/%.cpp,obj/%.o,$(SRC))

# Main purpose of the build
all: create_dirs $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Rule for object files
obj/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories bin/ and obj/
create_dirs:
	mkdir -p bin obj

# Cleaning up the project
clean:
	rm -rf bin obj

# Rebuild
rebuild: clean all

# Starting the program
run: all
	./$(TARGET)

.PHONY: all clean rebuild run