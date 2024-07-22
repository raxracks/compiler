#include <args.h>
#include <string.h>
#include <assert.h>

char* arg_proceeding(int argc, char** argv, char* arg, char* default_return) {
    for(int i = 0; i < argc - 1; i++) {
        if(strcmp(argv[i], arg) == 0) {
            return argv[i + 1];
        }
    }

    return default_return;
}

char* find_flagless_arg(int argc, char** argv, char* default_return) {
    for(int i = 1; i < argc; i++) {
        if(argv[i - 1][0] != '-' && argv[i][0] != '-') {
            return argv[i];
        }
    }

    return default_return;
}

void skip_args(int* argc, char*** argv, int n) {
    *argc -= n;
    *argv += n;
}

Args parse_args(int argc, char** argv) {
    assert(argc > 1);
    skip_args(&argc, &argv, 1);
    Args args = { 0 };

    if(argc == 1) {
        args.input = argv[0];
    } else {
        if(strcmp(argv[0], "build") == 0) {
            args.build = 1;
            args.output = arg_proceeding(argc, argv, "-o", "a.out");
        }

        args.input = find_flagless_arg(argc, argv, NULL);
        args.comp_debug = arg_proceeding(argc, argv, "-d", NULL) != NULL;
    }

    return args;
}