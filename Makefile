# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -O2

# Project root macro for the code
CXXFLAGS += -DPROJECT_SOURCE_DIR=\"$(shell pwd | sed 's/ /\\ /g')\"

# Source and object files
SRC_DIR = src
OBJ_DIR = obj
BIN = pfsp

SRCS = $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Include path (if needed)
INCLUDES = -Iinclude

# Default rule
all: $(BIN)

# Link
$(BIN): $(OBJS)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(OBJS) -o bin/$(BIN)

# Compile each .cpp into .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean everything
clean:
	rm -rf $(OBJ_DIR) bin

.PHONY: all clean
