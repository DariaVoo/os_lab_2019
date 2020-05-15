#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

//#define BUFSIZE 100
#define SADDR struct sockaddr
#define SIZE sizeof(struct sockaddr_in)

int main(int argc, char *argv[])
{
	int fd;
	int nread;
	struct sockaddr_in servaddr;
	if (argc < 4) {
		printf("Too few arguments \n");
		printf("usage %s <IP(0.0.0.0)> <port(10050)> <BufSize for msg>\n", argv[0]);
		exit(1);
	}

	int buff_size = atoi(argv[3]);
	char buf[buff_size];

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket creating");
		exit(1);
	}

	memset(&servaddr, 0, SIZE);
	servaddr.sin_family = AF_INET;

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		perror("bad address");
		exit(1);
	}

	servaddr.sin_port = htons(atoi(argv[2]));

	if (connect(fd, (SADDR *)&servaddr, SIZE) < 0) {
		perror("connect");
		exit(1);
	}

	write(1, "Input message to send\n", 22);
	while ((nread = read(0, buf, buff_size)) > 0) {
		if (write(fd, buf, nread) < 0) {
			perror("write");
			exit(1);
		}
	}

	close(fd);
	exit(0);
}
