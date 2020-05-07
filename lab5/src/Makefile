HEADERS =
CFLAGS := -Wall -Wextra -Werror

SRC_MUTEX = mutex.c
OBJ_MUTEX = $(patsubst %.c, %.o, $(SRC_MUTEX))

all: mutex

mutex: $(SRC_MUTEX) $(OBJ_MUTEX)
	$(CC) $(CFLAGS) $(OBJ_MUTEX) -lpthread -o mutex

%.o: %.c $(HEADERS)
	gcc $(CFLAGS) -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all