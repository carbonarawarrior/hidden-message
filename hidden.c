#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef CMD
#define CMD "cmd"
#endif

#ifndef PASS
#define PASS "pass"
#endif

#ifndef MESSAGE
#define MESSAGE "message"
#endif
extern char **environ;

void sendNotification(char *message) {
    if (fork() == 0) {
	char *notifyPath = "/usr/bin/notify-send";
	char *nargv[] = { notifyPath, message, NULL};
	execve(notifyPath, nargv, environ);
	printf("execve failed . . .");
	exit(1);
    }
}

int main(int argc, char **argv) {
    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/comm", getppid());

    FILE *f = fopen(path, "r");
    if (f == NULL) {
	printf("Error: Couldnt open path: %s\n", path);
	return 1;
    }

    char parent[256];
    if (!fgets(parent, sizeof(parent), f)) {
	strcpy(parent, "unknown");
    }
    fclose(f);

    parent[strcspn(parent, "\n")] = 0;

    char *m = MESSAGE;
    if (argc >= 2 && strcmp(PASS, argv[1]) == 0) {
	printf("%s", m);
	sendNotification(m);
    } else {
	printf("%s: %s: command not found\n", parent, CMD);
    }

    return 0;
}
