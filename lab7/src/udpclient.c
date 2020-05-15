#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

//#define SERV_PORT 20001
//#define BUFSIZE 1024
#define SADDR struct sockaddr
#define SLEN sizeof(struct sockaddr_in)

int main(int argc, char **argv)
{
	int sockfd, n;
	struct sockaddr_in servaddr;
//  struct sockaddr_in cliaddr;

	if (argc != 4) {
		printf("usage: %s <IPaddress of server> <port(20001)> <buf_size for msg(1024)>\n", argv[0]);
		exit(1);
	}

	int buf_size = atoi(argv[3]);
	char sendline[buf_size], recvline[buf_size + 1];

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0) {
		perror("inet_pton problem");
		exit(1);
	}
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket problem");
		exit(1);
	}

	write(1, "Enter string\n", 13);

	while ((n = read(0, sendline, buf_size)) > 0) {
		if (sendto(sockfd, sendline, n, 0, (SADDR *)&servaddr, SLEN) == -1) {
			perror("sendto problem");
			exit(1);
		}

		if (recvfrom(sockfd, recvline, buf_size, 0, NULL, NULL) == -1) {
			perror("recvfrom problem");
			exit(1);
		}

		printf("REPLY FROM SERVER= %s\n", recvline);
	}
	close(sockfd);
}
