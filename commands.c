#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/types.h>
#include<sys/wait.h>
#include "smash.h"
#include "history.c"

int firstSequenceNumber = 1;
int commandNumber = 0;
int argloc = 0;
int exitStatus = 0;

void executeExternalCommand(char *argv[]) {
	int pid = fork();
	if (pid == 0) {
		if (execvp(argv[0], argv) < 0) {
			exit(1);
		}
		else {
		exit(0);
		}
	}
	else if (pid > 0) {
		wait(&exitStatus);
	}
	else {
		perror("Fork failed");
		exit(1);
	}
}
void executeCommand(char *str) {
	int stringLength = strlen(str);
	if (isspace(str[stringLength-1]) || (stringLength == 0)) {
		exit(0);
	}
	else {
		char *parsingstr = (char*)malloc(strlen(str) + 1);
		strncpy(parsingstr, str, (strlen(str) + 1));
		char *token = strtok(parsingstr, " ");
		char *args[10000] = { NULL };
		int ret, i = 0;
		if (commandNumber == 0) {
			init_history();
		}

		while (token != NULL) {
			args[i] = token;
			token = strtok(NULL, " ");
			i++;
		}

		if ((args[0][0] == EOF) || (strcmp(args[0], "exit") == 0)) {
			clear_history();
			free(parsingstr);
			exit(0);
		}
		else if (strcmp(args[0], "cd") == 0) {
			if (args[1] != NULL) {
				ret = chdir(args[1]);
				if (ret != 0) {
					perror(args[1]);
					add_history(str, 1);
					commandNumber++;
				}
				else {
					fprintf(stdout, "%s\n", str);
					add_history(str, 0);                                
					commandNumber++;
				}
			}
		}                                      
		else if (strcmp(args[0], "history") == 0) {
			add_history(str, 0);
			commandNumber++; 
			if (commandNumber > 9) {
				firstSequenceNumber = commandNumber - 9;
				print_history(firstSequenceNumber);
			}
			else {
				print_history(firstSequenceNumber);
			}
		}

		else {
			executeExternalCommand(args);
			if (WIFEXITED(exitStatus)) {
				add_history(str, exitStatus);
				commandNumber++;
			}
		}
		free(parsingstr);
		parsingstr = NULL;
	}
}
