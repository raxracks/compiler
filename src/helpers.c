#include <helpers.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char* gen_ident(int indent) {
    char* text = malloc(sizeof(char) * (indent + 1));
    memset(text, ' ', indent);
    text[indent] = '\0';
    return text;
}

Args parse_args(int argc, char* argv[]) {
    assert(argc > 2);
    int build = 0;
    if(strcmp(argv[1], "build") == 0) {
        build = 1;
        assert(argc > 3 && "Build needs an input and output filename.");
    } else assert(strcmp(argv[1], "run") == 0 && "You must specify to either build or run.");

    return (Args){ 
        .input = argv[2], 
        .output = build ? argv[3] : NULL, 
        .build = build
    };
}