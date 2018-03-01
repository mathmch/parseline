#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "stage.h"
/*#include "util.c"*/

#define MAX_COMMAND_LENGTH 512
#define MAX_ARGUMENTS 10
#define MAX_PIPES 10

void parse_line(char command[]);
void get_line(char command[]);

int main(int argc, char *argv[]){
    char command[MAX_COMMAND_LENGTH*2];
    if (argc != 1){
        fprintf(stderr, "usage: parseline\n");
        exit(EXIT_FAILURE);
    }
    printf("line: ");
    parse_line(command);
    return 0;
}


void parse_line(char command[]){
    char *token;
    get_line(command);
    token = strtok(command, " ");
    do {
	
    } while ((token = strtok(NULL, " ")) != NULL);
}


void get_line(char command[]){
    if (fgets(command, MAX_COMMAND_LENGTH*2, stdin) == NULL) {
        perror("Read Command");
        exit(EXIT_FAILURE);
    }
    if (strlen(command) > MAX_COMMAND_LENGTH) {
        fprintf(stderr, "command too long\n");
        exit(EXIT_FAILURE);
    }
    printf("\n");
}
