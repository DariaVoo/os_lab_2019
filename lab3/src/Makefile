CC = gcc
INCLUDES := -I .

# When the work is done add the flags
CFLAGS := -Wall -Wextra -Werror

HEADERS = utils.h find_min_max.h

SRC_SEQUENTIAL = utils.c find_min_max.c sequential_min_max.c print_arr.c get_next_line.c
OBJ_SEQUENTIAL = $(patsubst %.c, %.o, $(SRC_SEQUENTIAL))

SRC_PARALLEL = utils.c find_min_max.c parallel_min_max.c ft_itoa.c print_arr.c get_next_line.c
OBJ_PARALLEL = $(patsubst %.c, %.o, $(SRC_PARALLEL))

SRC_FE = fork_with_exec.c
OBJ_FE = $(patsubst %.c, %.o, $(SRC_FE))

all: sequential_min_max parallel_min_max fork_with_exec

fork_with_exec: sequential_min_max $(OBJ_FE)
	$(CC) $(CFLAGS) $(OBJ_FE) $(INCLUDES) -o fork_with_exec

sequential_min_max: $(SRC_SEQUENTIAL) $(OBJ_SEQUENTIAL)
	$(CC) $(CFLAGS) $(OBJ_SEQUENTIAL) $(INCLUDES) -o sequential_min_max

parallel_min_max: $(SRC_PARALLEL) $(OBJ_PARALLEL)
	$(CC) $(CFLAGS) $(OBJ_PARALLEL) $(INCLUDES) -o parallel_min_max

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ_SEQUENTIAL)
	rm -f $(OBJ_PARALLEL)
	rm -f $(OBJ_FE)

fclean: clean
	rm -f sequential_min_max
	rm -f parallel_min_max
	rm -f fork_with_exec

re: fclean all
