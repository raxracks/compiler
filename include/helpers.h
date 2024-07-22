#ifndef __HELPERS_H__
#define __HELPERS_H__

typedef struct Args {
    const char* input;
    const char* output;
    int build;
} Args;

char* gen_ident(int indent);
Args parse_args(int argc, char* argv[]);

#endif