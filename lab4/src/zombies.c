#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

/* *
 * чтобы увидеть зомби процесс, выполните в терминале
 * ps aux | grep defunct
 * или чтобы увидеть родителя и его зомби-процесс
 * ps -e --format pid,ppid,stat,cmd
 * */
int main()
{
	pid_t child_pid;

	/* Создание дочернего процесса. */
	child_pid = fork();
	if (child_pid > 0) {
		/* Это родительский процесс — делаем минутную паузу. */
		printf("I am parent and I need some sleep\n");
		sleep(60);
		printf("I am wake up!\n");
		printf("Let's kill the zombie!\n");
		wait(NULL);
	} else {
		/* Это дочерний процесс — немедленно завершаем работу.*/
		printf("I will be zombie\n");
		exit(0);
	}
	return 0;
}