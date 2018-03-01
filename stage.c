#include <stdio.h>
#include "stage.h"

void print_stage(struct stage *st) {
    int i;
    printf("--------\n");
    printf("Stage %d\n", st->number);
    printf("--------\n");
    printf("     input: %s\n", st->input);
    printf("    output: %s\n", st->output);
    printf("      argc: %d\n", st->argc);
    printf("      argv: ");
    for (i = 0; i < st->argc; i++) {
        printf("\"%s\"", st->argv[i]);
        if (st->argc != 1 && i < st->argc - 1)
            printf(",");
    }

    printf("\n\n");
}
