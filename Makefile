CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -g -Iinclude
BUILD_DIR := build
TARGET := $(BUILD_DIR)/campusguard

SRCS := $(shell find src -name '*.cpp')
OBJS := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
