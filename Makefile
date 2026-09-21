CXX ?= g++
TARGET ?= maiden
DEBUG_TARGET ?= maiden-debug
BUILD_DIR ?= build
DEBUG_BUILD_DIR ?= build/debug
ARGS ?=

SRCS := $(shell find . -type f -name '*.cpp' -not -path './$(BUILD_DIR)/*')
OBJS := $(patsubst ./%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEBUG_OBJS := $(patsubst ./%.cpp,$(DEBUG_BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d) $(DEBUG_OBJS:.o=.d)

HEADER_DIRS := $(shell find . -type f \( -name '*.hpp' -o -name '*.h' \) -exec dirname {} \; | sort -u)
INCLUDES := $(addprefix -I,$(HEADER_DIRS))

CPPFLAGS += $(INCLUDES) -MMD -MP
CXXFLAGS ?= -std=c++20 -Wall -Wextra -pedantic -g
SANITIZERS ?= -fsanitize=address,undefined
STL_DEBUG ?=
DEBUG_CPPFLAGS ?= -DDEBUG $(STL_DEBUG)
DEBUG_CXXFLAGS ?= -std=c++20 -Wall -Wextra -pedantic -O0 -g3 -ggdb \
	-fno-omit-frame-pointer -fno-optimize-sibling-calls $(SANITIZERS)
DEBUG_LDFLAGS ?= $(SANITIZERS)
LDFLAGS ?=
LDLIBS ?=

.PHONY: all debug run debug-run gdb clean print-vars

all: $(TARGET)

debug: $(DEBUG_TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(DEBUG_TARGET): $(DEBUG_OBJS)
	$(CXX) $(LDFLAGS) $(DEBUG_LDFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(DEBUG_BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(DEBUG_CPPFLAGS) $(DEBUG_CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) $(ARGS)

debug-run: $(DEBUG_TARGET)
	ASAN_OPTIONS=detect_leaks=1:abort_on_error=1:strict_string_checks=1 \
	UBSAN_OPTIONS=print_stacktrace=1 \
	./$(DEBUG_TARGET) $(ARGS)

gdb: $(DEBUG_TARGET)
	gdb --args ./$(DEBUG_TARGET) $(ARGS)

clean:
	rm -rf $(BUILD_DIR) $(DEBUG_BUILD_DIR) $(TARGET) $(DEBUG_TARGET)

print-vars:
	@echo "SRCS=$(SRCS)"
	@echo "OBJS=$(OBJS)"
	@echo "DEBUG_OBJS=$(DEBUG_OBJS)"
	@echo "HEADER_DIRS=$(HEADER_DIRS)"
	@echo "INCLUDES=$(INCLUDES)"

-include $(DEPS)
