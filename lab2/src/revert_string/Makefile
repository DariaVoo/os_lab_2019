# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snorcros <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/08 02:16:22 by snorcros          #+#    #+#              #
#    Updated: 2020/02/08 02:16:23 by snorcros         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = revert
CFLAGS := -Wall -Wextra -Werror

SRCS = main.c revert_string.c ft_strlen.c

OBJ_DIR = objects/
OBJ_LST = $(patsubst %.c, %.o, $(SRCS))
OBJ	= $(addprefix $(OBJ_DIR), $(OBJ_LST))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(INCLUDES) $(LIB_FLAG) -o $(NAME)

$(LIBFT):
	make -sC $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

objects/%.o : %.c $(HEADERS)
	gcc $(CFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
