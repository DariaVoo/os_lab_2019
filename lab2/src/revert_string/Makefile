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
NAMESTATIC = revstatic
NAMESHARED = revshared
STATICLIB = librevert.a
SHAREDLIB = librevert.so
CFLAGS := -Wall -Wextra -Werror

HEADERS = includes
SRCS = main.c revert_string.c ft_strlen.c
MAIN = main.c
MAIN_OBJ =  $(patsubst %.c, %.o, $(MAIN))
LIB_SRCS = revert_string.c ft_strlen.c
LIB_OBJ = $(patsubst %.c, %.o, $(LIB_SRCS))

OBJ_DIR = objects/
OBJ_LST = $(patsubst %.c, %.o, $(SRCS))
OBJ	= $(addprefix $(OBJ_DIR), $(OBJ_LST))

all: $(NAME)

$(NAME):  $(OBJ_DIR) $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(INCLUDES) $(LIB_FLAG) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

objects/%.o : %.c $(HEADERS)
	gcc $(CFLAGS) -c -I $(HEADERS) $< -o $@

#Create static lib
staticlib: $(STATICLIB)

$(STATICLIB): $(LIB_SRCS) $(LIB_OBJ)
	ar rcs $(STATICLIB) $(LIB_OBJ)

%.o: %.c $(HEADER)
	gcc -Wall -Wextra -Werror -c $< -I $(HEADERS)

#Link with static lib
linkstatic: $(MAIN) $(STATICLIB)
	gcc $(CFLAGS) -c -I $(HEADERS) $(MAIN) -o $(MAIN_OBJ)
	gcc $(MAIN_OBJ) -L . -lrevert -o $(NAMESTATIC)

#Create sharedlib
sharedlib: $(SHAREDLIB)

$(SHAREDLIB): $(LIB_SRCS) $(LIB_OBJ)
	gcc -shared $(LIB_OBJ) -o $(SHAREDLIB)

%.o: %.c $(HEADER)
	gcc -Wall -Wextra -Werror -c -fPIC $< -I $(HEADERS)

#Link with shared lib
linkshared: $(MAIN) $(SHAREDLIB)
	gcc $(CFLAGS) -c -I $(HEADERS) $(MAIN) -o $(MAIN_OBJ)
	gcc $(MAIN_OBJ) -L./ -lrevert -o $(NAMESHARED)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(LIB_OBJ)
	rm -rf $(MAIN_OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(STATICLIB)
	rm -f $(SHAREDLIB)
	rm -f $(NAMESHARED)
	rm -f $(NAMESTATIC)

re: fclean all

.PHONY: all clean fclean re
