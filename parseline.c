#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "stage.h"
#include "util.h"

#define MAX_COMMAND_LENGTH 512

typedef enum { none, expecting, received } redirect_status;

void parse_line(char command[]);
void get_line(char command[]);
void parse_stage(char *command, struct stage *stage, int current_stage, int total_stages);
void handle_invalid_redirection(int argc, char *argv[], bool is_input);

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

void parse_stage(char *command, struct stage *stage, int current_stage, int total_stages) {
    char input[INPUT_MAX];
    char output[OUTPUT_MAX];
    int argc = 0;
    char *argv[MAX_ARGUMENTS];
    redirect_status input_status = none;
    redirect_status output_status = none;
    char *token;
    const char *delim = " \n";

    input[0] = '\0';
    output[0] = '\0';

    for (token = strtok(command, delim); token != NULL; token = strtok(NULL, delim)) {
        if (strcmp(token, "<") == 0) {
            /* input redirection */
            if (current_stage != 0 || input_status || output_status)
                handle_invalid_redirection(argc, argv, input_status != none);
            input_status = expecting;
        } else if (strcmp(token, ">") == 0) {
            /* output redirection */
            if (current_stage != total_stages - 1 || input_status || output_status)
                handle_invalid_redirection(argc, argv, input_status != none);
            output_status = expecting;
        } else if (input_status == expecting) {
            /* record input redirection source */
            strcpy(input, token);
            input_status = received;
        } else if (output_status == expecting) {
            /* record output redirection source */
            strcpy(output, token);
            output_status = received;
        } else {
            /* command name or argument */
            argv[argc] = token;
            argc++;
        }
    }

    if (input_status == expecting)
        handle_invalid_redirection(argc, argv, true);
    else if (output_status == expecting)
        handle_invalid_redirection(argc, argv, false);

    setup_stage(stage, current_stage, input, output, argc, argv, total_stages);
}

void handle_invalid_redirection(int argc, char *argv[], bool is_input) {
    char *source = (argc != 0) ? argv[0] : is_input ? "<" : ">";
    char *redirect_type = is_input ? "input" : "output";
    fprintf(stderr, "%s: bad %s redirection\n", source, redirect_type);
    exit(EXIT_FAILURE);
}
