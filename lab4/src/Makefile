CC = gcc
INCLUDES := -I .

# When the work is done add the flags
CFLAGS := -Wall -Wextra -Werror

# task2
SRC_ZOMBIES = zombies.c
OBJ_ZOMBIES = $(patsubst %.c, %.o, $(SRC_ZOMBIES))
# task3
SRC_PROCMEM = process_memory.c
OBJ_PROCMEM = $(patsubst %.c, %.o, $(SRC_PROCMEM))

# task5
SRC_PTHREADS = sum_array.c
OBJ_PTHREADS = $(patsubst %.c, %.o, $(SRC_PTHREADS))

LIB_DIR = libarray/
LIB = $(LIB_DIR)libarray.a
LIB_HEADERS = -I $(LIB_DIR)includes/
LIB_FLAG := -L./$(LIB_DIR) -larray

all: zombies

zombies: $(SRC_ZOMBIES) $(OBJ_ZOMBIES)
	$(CC) $(CFLAGS) $(OBJ_ZOMBIES) $(INCLUDES) -o zombies

process_memory: $(SRC_PROCMEM)
	$(CC) -c $(SRC_PROCMEM)
	$(CC) $(OBJ_PROCMEM) $(INCLUDES) -o process_memory

posix_threads: $(LIB) $(SRC_PTHREADS)
	$(CC) $(CFLAGS) $(LIB_HEADERS)  -c $(SRC_PTHREADS)
	$(CC) $(CFLAGS) $(OBJ_PTHREADS) $(INCLUDES) $(LIB_HEADERS) $(LIB_FLAG) -o posix_threads

$(LIB):
	make -sC $(LIB_DIR)

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< $(INCLUDES)

clean:
	rm -f $(OBJ_ZOMBIES)
	rm -f $(OBJ_PROCMEM)
	make -sC $(LIB_DIR) clean
	rm -f $(OBJ_PTHREADS)

fclean: clean
	rm -f zombies
	rm -f process_memory
	make -sC $(LIB_DIR) fclean
	rm -f posix_threads

re: fclean all
