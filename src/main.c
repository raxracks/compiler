#define SL_IMPLEMENTATION
#include <slibs/slibs.h>

#include <tokenizer.h>
#include <ast.h>
#include <codegen.h>
#include <binary.h>
#include <helpers.h>

int main(int argc, char* argv[]) {
    Args args = parse_args(argc, argv);

    sl_string buffer = { 0 };
    sl_read_file(args.input, &buffer);

    printf("Tokens:\n");
    TokenVec tokens = { 0 };
    tokenize(sl_c_str(buffer), &tokens);
    tokens_print(tokens);
    printf("\n");

    printf("AST:\n");
    ASTNode* program = ast_parse(&tokens);
    ast_print(program, 0);
    printf("\n");

    printf("Codegen:\n");
    const char* code = codegen(program);
    printf("%s\n\n", code);

    binary_produce(code, args);

    return 0;
}