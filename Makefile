CXX ?= g++
TARGET ?= compiler
BUILD_DIR ?= build

SRCS := $(shell find . -type f -name '*.cpp' -not -path './$(BUILD_DIR)/*')
OBJS := $(patsubst ./%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

HEADER_DIRS := $(shell find . -type f \( -name '*.hpp' -o -name '*.h' \) -exec dirname {} \; | sort -u)
INCLUDES := $(addprefix -I,$(HEADER_DIRS))

CPPFLAGS += $(INCLUDES) -MMD -MP
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -g
LDFLAGS ?=
LDLIBS ?=

.PHONY: all run clean print-vars

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

print-vars:
	@echo "SRCS=$(SRCS)"
	@echo "OBJS=$(OBJS)"
	@echo "HEADER_DIRS=$(HEADER_DIRS)"
	@echo "INCLUDES=$(INCLUDES)"

-include $(DEPS)
