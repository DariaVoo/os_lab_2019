NAME = libfactorial.a
HEADERS = factorial.h
CFLAGS := -Wall -Wextra -Werror

SRCS = get_next_line.c factorial.c mult_modulo.c
OBJ = $(patsubst %.c, %.o, $(SRCS))

all: $(NAME)

$(NAME): $(SRCS) $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c $(HEADERS)
	gcc $(CFLAGS) -c $< -I .

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all