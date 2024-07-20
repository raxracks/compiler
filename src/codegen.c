#include <codegen.h>
#include <slibs/slibs.h>

const char* codegen(ASTNode* node) {
    if(node->type == AST_PROGRAM) {
        sl_string code = sl_string("#include <std.h>\n\nint main() {\n");
        for(sl_vec_it(n, node->body)) {
            sl_append_c_str(&code, codegen(*n));
            sl_append_c_str(&code, ";\n");
        }
        sl_append_c_str(&code, "}");
        return sl_c_str(code);
    }

    if(node->type == AST_CALL_EXPRESSION) {
        sl_string code = sl_string(node->name);
        sl_append_c_str(&code, "(");
        for(size_t i = 0; i < node->params.size; i++) {
            sl_append_c_str(&code, codegen(node->params.data[i]));
            if(i < node->params.size - 1) {
                sl_append_c_str(&code, ", ");
            }
        }
        sl_append_c_str(&code, ")");
        return sl_c_str(code);
    }

    if(node->type == AST_NUMBER_LITERAL) {
        return node->value;
    }

    if(node->type == AST_STRING_LITERAL) {
        sl_string code = sl_string("\"");
        sl_append_c_str(&code, node->value);
        sl_append_c_str(&code, "\"");
        return sl_c_str(code);
    }

    return "";
}