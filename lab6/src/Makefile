CC = gcc
CFLAGS := -Wall -Wextra -Werror

SRC_CLIENT = client.c
OBJ_CLIENT = $(patsubst %.c, %.o, $(SRC_CLIENT))

SRC_SERVER = server.c
OBJ_SERVER = $(patsubst %.c, %.o, $(SRC_SERVER))

LIB_DIR = libfactorial/
LIB = $(LIB_DIR)libfactorial.a
LIB_HEADERS = -I $(LIB_DIR)/
LIB_FLAG := -L./$(LIB_DIR) -lfactorial

HEADERS  = $(LIB_DIR)factorial.h
INCLUDES := -I $(LIB_DIR)

all: client server

client: $(LIB) $(SRC_CLIENT) $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(INCLUDES) $(LIB_FLAG) -lpthread -o client

server: $(LIB) $(SRC_SERVER) $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(INCLUDES) $(LIB_FLAG) -lpthread -o server

$(LIB):
	make -sC $(LIB_DIR)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $(LIB_FLAG) $< -o $@

clean:
	rm -f $(OBJ_CLIENT)
	rm -f $(OBJ_SERVER)
	make -sC $(LIB_DIR) clean

fclean: clean
	rm -f client
	rm -f server
	make -sC $(LIB_DIR) fclean

re: fclean all
