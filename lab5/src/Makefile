HEADERS =
CC := gcc
CFLAGS := -Wall -Wextra -Werror

SRC_MUTEX = mutex.c
OBJ_MUTEX = $(patsubst %.c, %.o, $(SRC_MUTEX))

SRC_FAC = factorial.c
OBJ_FAC = $(patsubst %.c, %.o, $(SRC_FAC))


all: mutex

mutex: $(SRC_MUTEX) $(OBJ_MUTEX)
	$(CC) $(CFLAGS) $(OBJ_MUTEX) -lpthread -o mutex

factorial: $(SRC_FAC) $(OBJ_FAC)
	$(CC) $(CFLAGS) $(OBJ_FAC) -lpthread -o factorial

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ_MUTEX)
	rm -f $(OBJ_FAC)

fclean: clean
	rm -f mutex
	rm -f fatorial

re: fclean all