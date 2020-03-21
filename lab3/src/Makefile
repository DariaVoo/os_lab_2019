CC = gcc
INCLUDES := -I .

# When the work is done add the flags
CFLAGS := # -Wall -Wextra -Werror

HEADERS = utils.h find_min_max.h

SRC_SEQUENTIAL = utils.c find_min_max.c sequential_min_max.c
OBJ_SEQUENTIAL = $(patsubst %.c, %.o, $(SRC_SEQUENTIAL))

SRC_PARALLEL = utils.c find_min_max.c parallel_min_max.c
OBJ_PARALLEL = $(patsubst %.c, %.o, $(SRC_PARALLEL))

all: sequential_min_max parallel_min_max

sequential_min_max: $(SRC_SEQUENTIAL) $(OBJ_SEQUENTIAL)
	$(CC) $(CFLAGS) $(OBJ_SEQUENTIAL) $(INCLUDES) -o sequential_min_max

parallel_min_max: $(SRC_PARALLEL) $(OBJ_PARALLEL)
	$(CC) $(CFLAGS) $(OBJ_PARALLEL) $(INCLUDES) -o parallel_min_max

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ_SEQUENTIAL)
	rm -f $(OBJ_PARALLEL)

fclean: clean
	rm -f sequential_min_max
	rm -f parallel_min_max

re: fclean all
