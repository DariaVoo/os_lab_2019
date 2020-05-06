NAME = libarray.a
HEADERS = includes
CFLAGS := -Wall -Wextra -Werror

SRCS = generate_array.c print_arr.c sum_arr.c
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
