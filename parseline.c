#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "stage.h"
#include "util.h"

#define MAX_COMMAND_LENGTH 512

void parse_line(char command[]);
void parse_stage(char *command, struct stage *stage, int current_stage, int total_stages);
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


void parse_line(char command[]) {
    struct stage stages[MAX_PIPES + 1];
    char *token;
    int total_stages;
    int i;

    get_line(command);
    total_stages = count_occurrences(command, '|') + 1;
    token = strtok(command, "|");
    for (i = 0; i < total_stages; i++) {
        parse_stage(token, &stages[i], i, total_stages);
        token = strtok(NULL, "|");
    }

    for (i = 0; i < total_stages; i++)
        print_stage(&stages[i]);
}

void parse_stage(char *command, struct stage *stage, int current_stage, int total_stages) {
    char input[INPUT_MAX];
    char output[OUTPUT_MAX];
    int argc = 0;
    char *argv[MAX_ARGUMENTS];
    char *token;
    int token_number = 0;

    input[0] = '\0';
    output[0] = '\0';

    token = strtok(command, " ");
    while (token != NULL) {
        if (strcmp(token, "<") == 0) {
            /* input redirection */
            if (current_stage != 0 || token_number == 0) {
                /* bail */
            }
            if ((token = strtok(NULL, " ")) == NULL) {
                /* bail */
            }
            token_number++;
            strcpy(input, token);
        } else if (strcmp(token, ">") == 0) {
            /* output redirection */
            if (current_stage != total_stages - 1 || token_number == 0) {
                /* bail */
            }
            if ((token = strtok(NULL, " ")) == NULL) {
                /* bail */
            }
            token_number++;
            strcpy(output, token);
        } else if (strcmp(token, "|") == 0) {
            /* bail */
        } else {
            /* command name or argument */
            argv[argc] = token;
            argc++;
        }

        token = strtok(NULL, " ");
        token_number++;
    }

    setup_stage(stage, current_stage, input, output, argc, argv, total_stages);
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
