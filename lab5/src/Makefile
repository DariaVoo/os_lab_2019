HEADERS =
CC := gcc
CFLAGS := -Wall -Wextra -Werror

SRC_MUTEX = mutex.c
OBJ_MUTEX = $(patsubst %.c, %.o, $(SRC_MUTEX))

SRC_FAC = factorial.c
OBJ_FAC = $(patsubst %.c, %.o, $(SRC_FAC))

SRC_DEAD = deadlock.c
OBJ_DEAD = $(patsubst %.c, %.o, $(SRC_DEAD))

all: mutex

mutex: $(SRC_MUTEX) $(OBJ_MUTEX)
	$(CC) $(CFLAGS) $(OBJ_MUTEX) -lpthread -o mutex

factorial: $(SRC_FAC) $(OBJ_FAC)
	$(CC) $(CFLAGS) $(OBJ_FAC) -lpthread -o factorial

deadlock: $(SRC_DEAD) $(OBJ_DEAD)
	$(CC) $(CFLAGS) $(OBJ_DEAD) -lpthread -o deadlock

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ_MUTEX)
	rm -f $(OBJ_FAC)
	rm -f $(OBJ_DEAD)

fclean: clean
	rm -f mutex
	rm -f fatorial
	rm -f deadlock

re: fclean all