#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 512
#define MAX_ARGUMENTS 10
#define MAX_PIPES 10

void parse_line(char command[]);
void get_line(char command[]);
void print_stage(int stage, char *input, char *output, int argc, char *argv[]);

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
    get_line(command);
    
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
}

void print_stage(int stage, char *input, char *output, int argc, char *argv[]){
    int i;
    printf("--------\n");
    printf("Stage %d\n", stage);
    printf("--------\n");
    printf("     input: %s\n", input);
    printf("    output: %s\n", output);
    printf("      argc: %d\n", argc);
    printf("      argv: ");
    for (i = 0; i < argc; i++) {
	printf("%s ", argv[i]);
    }
    printf("\n");

}
