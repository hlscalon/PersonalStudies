# CC := gcc
# CCP := g++
# CLIBS := libs/c
# DIR_ALGO := algorithms
# DIR_DATA_STRUCT := data_structures
# CFLAGS := -Wall -O3

# all: insertion_sort_test.o

# insertion_sort_test.o:
# 	$(CC) -I$(CLIBS) $(CFLAGS) \
# 	$(DIR_ALGO)/ordering/insertion_sort/c/insertion_sort.c \
# 	$(DIR_ALGO)/ordering/insertion_sort/c/insertion_sort_test.c \
# 	-o $(DIR_ALGO)/ordering/insertion_sort/c/insertion_sort_test.o

# run_tests: insertion_sort_test.o
# 	./$(DIR_ALGO)/ordering/insertion_sort/c/insertion_sort_test.o

BUILD_DIR = ./build
SRC_DIRS = ./src
TARGET_EXEC = a.out

SRCS := $(shell find $(SRC_DIRS) -iname *.cpp -or -iname *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
TARGET_EXECS := $(OBJS:.o=.out)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS = $(INC_FLAGS) -MMD -MP
CXXFLAGS = -Wall -O3 -std=c++17
CFLAGS = -Wall -O3 -std=c99

#$(BUILD_DIR)/$(TARGET_EXECS): $(OBJS)
$(TARGET_EXECS): $(OBJS)
	$(CXX) $(filter $(wildcard ./$(dir $@)*.o), $(OBJS)) -o $@ $(LDFLAGS)

# @echo "PRINTANDO............"
# @echo "OBJS........."
# @echo $(OBJS)
# @echo "@..........."
# @echo $@
# @echo "TARGET_EXECS........."
# @echo $(TARGET_EXECS)
# @echo "DIR..."
# @echo $(dir $@)
# @echo "FILTRADO..."
# @echo $(filter $(wildcard ./$(dir $@)*.o), $(OBJS))
# @echo $(wildcard ./$(dir $@)*.o)
# @echo $(filter-out ./build/./src/algorithms/ordering/insertion_sort/cpp/insertion_sort_test.cpp.o, $(OBJS))

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
