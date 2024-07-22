#include <binary.h>
#include <libtcc.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>

int binary_produce(const char* code, Args args) {
    TCCState* state = tcc_new();
    tcc_set_lib_path(state, "tcc");
    if(args.build) {
        assert(tcc_set_output_type(state, TCC_OUTPUT_EXE)       == 0);
    } else {
        assert(tcc_set_output_type(state, TCC_OUTPUT_MEMORY)    == 0);
    }

    assert(tcc_add_include_path(state, "std")                   == 0);
    assert(tcc_add_file(state, "std/std.c")                     == 0);
    assert(tcc_compile_string(state, code)                      == 0);

    if(args.build) {
        return tcc_output_file(state, args.output);
    } else {
        return tcc_run(state, 0, NULL);
    }
}