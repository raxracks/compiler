#define SL_IMPLEMENTATION
#include <slibs/slibs.h>
#include <tokenizer.h>
#include <ast.h>
#include <codegen.h>
#include <tcc/libtcc.h>

int main(int argc, char* argv[]) {
    assert(argc > 2);

    sl_string buffer = { 0 };
    sl_read_file(argv[1], &buffer);

    Token* root = tokenize(sl_c_str(buffer));
    printf("Tokens:\n");
    Token* curr = root;
    while(curr != NULL) {
        printf("%s: %s\n", TokenTypeText[curr->type], curr->value);
        curr = curr->next;
    }
    printf("\n");

    printf("AST:\n");
    ASTNode* program = ast_parse(&root);
    ast_print(program, 0);
    printf("\n");

    printf("Codegen:\n");
    const char* code = codegen(program);
    printf("%s\n\n", code);

    TCCState* state = tcc_new();
    assert(tcc_set_output_type(state, TCC_OUTPUT_EXE)   == 0);
    tcc_set_lib_path(state, "lib/tcc");
    assert(tcc_add_include_path(state, "runtime")       == 0);
    assert(tcc_add_file(state, "runtime/runtime.c")     == 0);
    assert(tcc_compile_string(state, code)              == 0);
    assert(tcc_output_file(state, argv[2])              == 0);

    printf("Binary produced: %s\n", argv[2]);
}