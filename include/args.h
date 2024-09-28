#ifndef __ARGS_H__
#define __ARGS_H__

typedef struct Args {
    const char* input;
    const char* output;
    int build;
    int comp_debug;
} Args;

Args parse_args(int argc, char** argv);

#endif
