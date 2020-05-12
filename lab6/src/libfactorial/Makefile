NAME = libfactorial.a
HEADERS = .
CFLAGS := -Wall -Wextra -Werror

SRCS = factorial.c mult_modulo.c
OBJ = $(patsubst %.c, %.o, $(SRCS))

all: $(NAME)

$(NAME): $(SRCS) $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c $(HEADERS)
	gcc $(CFLAGS) -c $< -I $(HEADERS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all