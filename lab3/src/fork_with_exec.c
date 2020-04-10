#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	pid_t pid;

	if (argc)
		printf("Hi! Now I will call sequential min max and go to sleep))\n");
	pid = fork();
	if (pid == -1) {
		printf("I can't fork :c\n");
		exit(1);
	}
	else if (pid == 0)
	{
		execv("sequential_min_max", argv);
		perror("exec one failed");
		exit(1);
	} else {
//		wait(NULL);
		printf("Hi! I almost wait))\n");
	}
	wait(NULL);
	printf("Bye!\n");
	return (0);
}

