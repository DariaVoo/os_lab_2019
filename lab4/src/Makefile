CC = gcc
INCLUDES := -I .

# When the work is done add the flags
CFLAGS := -Wall -Wextra -Werror

HEADERS =

SRC_ZOMBIES = zombies.c
OBJ_ZOMBIES = $(patsubst %.c, %.o, $(SRC_ZOMBIES))

all: zombies

zombies: $(SRC_ZOMBIES) $(OBJ_ZOMBIES)
	$(CC) $(CFLAGS) $(OBJ_ZOMBIES) $(INCLUDES) -o zombies

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ_ZOMBIES)

fclean: clean
	rm -f zombies

re: fclean all
