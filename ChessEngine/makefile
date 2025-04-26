# Set default build type
BUILD ?= Release

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

ifeq ($(BUILD),Debug)
    CXXFLAGS += -g -O0
else
    CXXFLAGS += -O2
endif
# Source and build directories
SRC_DIR = src
BUILD_DIR = build
TARGET = ChessEngine.exe

# Find all .cpp files recursively
SRCS := $(wildcard src/*.cpp src/Common/*.cpp src/Common/Movements/*.cpp src/Data/*.cpp src/Engine/*.cpp src/Interface/*.cpp)


# Create .o filenames
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Link all objects into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile each .cpp into .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean

