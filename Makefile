BUILD_DIR = ./build
SRC_DIRS = ./src
TARGET_EXEC = a.out
DEBUG = -g

SRCS := $(shell find $(SRC_DIRS) -iname *.cpp -or -iname *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
TARGET_EXECS := $(OBJS:.o=.out)
TARGET_TEST_CXX := $(filter %_test.out, $(SRCS:%.cpp=$(BUILD_DIR)/%.out))
TARGET_TEST_C := $(filter %_test.out, $(SRCS:%.c=$(BUILD_DIR)/%.out))

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS = $(INC_FLAGS) -MMD -MP
CXXFLAGS = -Wall -O3 -std=c++17
CFLAGS = -Wall -O3 -std=c99 $(DEBUG)

all: $(TARGET_TEST_C) $(TARGET_TEST_CXX)

$(TARGET_TEST_C): $(OBJS)
	$(CC) $(filter $(wildcard ./$(dir $@)*.o), $(OBJS)) -o $@ $(LDFLAGS)

$(TARGET_TEST_CXX): $(OBJS)
	$(CXX) $(filter $(wildcard ./$(dir $@)*.o), $(OBJS)) -o $@ $(LDFLAGS)

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P = mkdir -p
