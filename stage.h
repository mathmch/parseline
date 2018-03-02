#ifndef stage_h
#define stage_h

#define MAX_ARGUMENTS 10
#define MAX_PIPES 10
#define INPUT_MAX 18  /* strlen("pipe from stage 8") + 1 */
#define OUTPUT_MAX 16 /* strlen("pipe to stage 8") + 1 */

struct stage {
    int number;
    char input[INPUT_MAX];
    char output[OUTPUT_MAX];
    int argc;
    char *argv[MAX_ARGUMENTS];
};

void setup_stage(struct stage *stage, int number, char *input, char *output,
                 int argc, char *argv[], int total_stages);

void print_stage(struct stage *st);

#endif
