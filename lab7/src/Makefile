CC = gcc
CFLAGS := -Wall -Wextra -Werror

SRC_TCPCLIENT = tcpclient.c
OBJ_TCPCLIENT = $(patsubst %.c, %.o, $(SRC_TCPCLIENT))

SRC_TCPSERVER = tcpserver.c
OBJ_TCPSERVER = $(patsubst %.c, %.o, $(SRC_TCPSERVER))

SRC_UDPCLIENT = udpclient.c
OBJ_UDPCLIENT = $(patsubst %.c, %.o, $(SRC_UDPCLIENT))

SRC_UDPSERVER = udpserver.c
OBJ_UDPSERVER = $(patsubst %.c, %.o, $(SRC_UDPSERVER))

all: tcpclient tcpserver udpclient udpserver

tcpclient: $(SRC_TCPCLIENT) $(OBJ_TCPCLIENT)
	$(CC) $(CFLAGS) $(OBJ_TCPCLIENT) -o tcpclient

tcpserver: $(SRC_TCPSERVER) $(OBJ_TCPSERVER)
	$(CC) $(CFLAGS) $(OBJ_TCPSERVER)  -o tcpserver

udpclient: $(SRC_UDPCLIENT) $(OBJ_UDPCLIENT)
	$(CC) $(CFLAGS) $(OBJ_UDPCLIENT)  -o udpclient

udpserver: $(SRC_UDPSERVER) $(OBJ_UDPSERVER)
	$(CC) $(CFLAGS) $(OBJ_UDPSERVER)  -o udpserver

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_TCPCLIENT)
	rm -f $(OBJ_TCPSERVER)
	rm -f $(OBJ_UDPCLIENT)
	rm -f $(OBJ_UDPSERVER)

fclean: clean
	rm -f tcpclient
	rm -f udpclient
	rm -f tcpserver
	rm -f udpserver

re: fclean all