#define MAXLINE 4096
#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "smash.h"
#include "commands.c"

int main() {
	char bfr[MAXLINE];
	fputs("$ ",stderr);  //Output the first prompt
	//Loop reading commands until EOF or error
	while (fgets(bfr, MAXLINE, stdin) != NULL) {
		if (strlen(bfr) > 4090) {
			printf("Max characters exceeded\n");
		}
		else {
			bfr[strlen(bfr) - 1] = '\0'; //Replace newline with NUL
			executeCommand(bfr);
		}
		fputs("$ ",stderr);
	}

	return 0;
}