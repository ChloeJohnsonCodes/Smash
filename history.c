// References: https://www.programiz.com/dsa/linked-list-types

#include "history.h"

int i;
int j;
int initialized = 0;
struct Cmd *commands[10];
char commandStrings[1023];

void init_history() {
	for (i = 0; i < 10; i++) {
		commands[i] = malloc(sizeof(struct Cmd));
		commands[i]->cmd = NULL;
		commands[i]->exitStatus = 0;
		initialized = 1;

	}
	i = 0;
}
void add_history(char *cmd, int exitStatus) {
	if (i < 10) {
		commands[i]->cmd = strndup(cmd, 1023);
		commands[i]->exitStatus = exitStatus;
		i++;
	}
	else {
		j = 0;
		for (j = 0; j < 9; j++) {
			free(commands[j]->cmd);
			commands[j]->cmd = strndup(commands[j + 1]->cmd, 1023);
			commands[j]->exitStatus = commands[j + 1]->exitStatus;
		}
		free(commands[9]->cmd);
		commands[9]->cmd = NULL;
		commands[9]->cmd = strndup(cmd, 1023);
		commands[9]->exitStatus = exitStatus;
		i++;
	}
}

void clear_history() {
	int j = 0;
	while (j < 10) {
		if (commands[j]->cmd != NULL) {
			free(commands[j]->cmd);
			commands[j]->cmd = NULL;
		}
		free(commands[j]);
		commands[j] = NULL;
		j++;
	}
}

void print_history(int firstSequenceNumber) {
	if (initialized == 1) {
		int j = 0;
		while (j < 10) {
			if (commands[j]->cmd != NULL) {
				printf("%d [%d] %s\n", firstSequenceNumber, commands[j]->exitStatus, commands[j]->cmd);
				firstSequenceNumber++;
			}
			j++;
		}
	}
}