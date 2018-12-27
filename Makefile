CC := gcc
CCP := g++
CLIBS := libs/c
DIR_ALGO := algorithms
DIR_DATA_STRUCT := data_structures
CFLAGS := -Wall -O3

all: insertion_sort_test.o

insertion_sort_test.o:
	$(CC) -I$(CLIBS) $(CFLAGS) \
	$(DIR_ALGO)/ordering/insertion_sort/c/insertion_sort.c \
	$(DIR_ALGO)/ordering/insertion_sort/c/insertion_sort_test.c \
	-o $(DIR_ALGO)/ordering/insertion_sort/c/insertion_sort_test.o

run_tests: insertion_sort_test.o
	./$(DIR_ALGO)/ordering/insertion_sort/c/insertion_sort_test.o