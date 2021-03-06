#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>

#define LINE_MAX 256

int main() {
	char buffer[LINE_MAX] = {0};
	int len = 0;
	int pid = 0;
	int status = 0;

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
