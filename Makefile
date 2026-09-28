CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -g
BUILD_DIR := build
TARGET := $(BUILD_DIR)/campusguard
# Add include/ and every subfolder under include/ to the compiler search path.
INCLUDE_DIRS := $(shell find include -type d)
CPPFLAGS := $(addprefix -I,$(INCLUDE_DIRS))
# Automatically find every .cpp file under src/.
SRCS := $(shell find src -type f -name '*.cpp')
# Convert:
#   src/adapter/LegacyGatewayAdapter.cpp
# into:
#   build/adapter/LegacyGatewayAdapter.o
OBJS := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
.PHONY: all clean run rebuild
all: $(TARGET)
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^
$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
run: all
	./$(TARGET)
rebuild: clean all
clean:
	rm -rf $(BUILD_DIR)
