#define SL_IMPLEMENTATION
#include <slibs/slibs.h>

#include <tokenizer.h>
#include <ast.h>
#include <codegen.h>
#include <binary.h>
#include <args.h>

int main(int argc, char* argv[]) {
    Args args = parse_args(argc, argv);

    sl_string* input_str = sl_read_file(args.input);
    if(!input_str) return -1;
    char* input = sl_c_str(*input_str);

    int debug = args.comp_debug;
    if(debug) printf("Tokens:\n");
    TokenVec tokens = { 0 };
    tokenize(input, &tokens);
    if(debug) tokens_print(tokens);
    if(debug)  printf("\n");

    if(debug) printf("AST:\n");
    ASTNode* program = ast_parse(&tokens);
    if(debug) ast_print(program, 0);
    if(debug) printf("\n");

    if(debug) printf("Codegen:\n");
    const char* code = codegen(program);
    if(debug) printf("%s\n\n", code);

    binary_produce(code, args);

    return 0;
}