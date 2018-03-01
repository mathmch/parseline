#ifndef stage_h
#define stage_h

#define INPUT_MAX 18  /* strlen("pipe from stage 8") + 1 */
#define OUTPUT_MAX 16 /* strlen("pipe to stage 2") + 1 */

struct stage {
    int number;
    char input[INPUT_MAX];
    char output[OUTPUT_MAX];
    int argc;
    char *argv[];
};

#endif
