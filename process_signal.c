#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define LINE_MAX 256

void sig_interrupt(int);

int main() {
	char buffer[LINE_MAX] = {0};
	int len = 0;
	int pid = 0;
	int status = 0;
	
	if (signal(SIGINT, sig_interrupt) == SIG_ERR)
			perror("signal handler register error.");

	printf("%% ");
	while (fgets(buffer, LINE_MAX, stdin) != NULL) {
		if ((len = strlen(buffer)) == 0) continue;
		buffer[len - 1] = '\0';
		if ((pid = fork()) == 0) {
			execlp(buffer, buffer, (char*)0);
			exit(127);
		} 
		if ((pid = waitpid(pid, &status, 0)) < 0) {
			fputs("wait pid error", stderr);
		}
		printf("%% ");
	}
	return 0;
}

void sig_interrupt(int sig_no) {
	printf("interrupt\n%% ");
	fflush(stdout);
}
