#include <ast.h>
#include <helpers.h>

const char* ASTTypeText[] = {
    "Program",
    "CallExpression",
    "NumberLiteral",
    "StringLiteral"
};

ASTNode* ast_parse(TokenVec* tokens) {
    ASTVec body = { 0 };

    Token** end = sl_vec_end(*tokens);
    while(tokens->data != end) {
        sl_vec_push(body, ast_walk(tokens));
    }

    return ast_create_program(body);
}

ASTNode* ast_walk(TokenVec* tokens) {
    if(tokens->data[0]->type == TOKEN_NUMBER) {
        ASTNode* number = ast_create_number_literal(tokens->data[0]->value);
        sl_vec_forward(*tokens);
        return number;
    }

    if(tokens->data[0]->type == TOKEN_STRING) {
        ASTNode* string = ast_create_string_literal(tokens->data[0]->value);
        sl_vec_forward(*tokens);
        return string;
    }

    if(tokens->data[0]->type == TOKEN_LPAREN) { // Call expression
        sl_vec_forward(*tokens);
        const char* name = tokens->data[0]->value;
        ASTVec params = { 0 };

        sl_vec_forward(*tokens);

        while(tokens->data[0]->type != TOKEN_RPAREN) {
            sl_vec_push(params, ast_walk(tokens));
        }

        sl_vec_forward(*tokens);

        return ast_create_call_expression(name, params);
    }

    return NULL;
}

void ast_print(ASTNode* node, int indent) {
    switch(node->type) {
    case AST_PROGRAM:
        printf("%s%s\n%sBody:\n", 
            gen_ident(indent), ASTTypeText[node->type], 
            gen_ident(indent + 2));
        
        indent += 2;
        for(sl_vec_it(n, node->body)) {
            ast_print(*n, indent + 2);
        }
        break;

    case AST_CALL_EXPRESSION:
        printf("%s%s\n%sName: %s\n%sParams:\n", 
            gen_ident(indent), ASTTypeText[node->type], 
            gen_ident(indent + 2), node->name, 
            gen_ident(indent + 2));
        
        indent += 2;
        for(sl_vec_it(n, node->params)) {
            ast_print(*n, indent + 2);
        }
        break;
    
    case AST_NUMBER_LITERAL:
        printf("%s%s\n%sValue: %s\n", 
            gen_ident(indent), ASTTypeText[node->type], 
            gen_ident(indent + 2), node->value);
        break;

    case AST_STRING_LITERAL:
        printf("%s%s\n%sValue: %s\n", 
            gen_ident(indent), ASTTypeText[node->type], 
            gen_ident(indent + 2), node->value);
        break;
    }
}

ASTNode* ast_create_empty(ASTType type) {
    ASTNode* new_node = malloc(sizeof(ASTNode));
    new_node->type = type;
    return new_node;
}

ASTNode* ast_create_program(ASTVec body) {
    ASTNode* node = ast_create_empty(AST_PROGRAM);
    node->body = body;
    return node;
}

ASTNode* ast_create_call_expression(const char* name, ASTVec params) {
    ASTNode* node = ast_create_empty(AST_CALL_EXPRESSION);
    node->name = name;
    node->params = params;
    return node;
}

ASTNode* ast_create_number_literal(const char* value) {
    ASTNode* node = ast_create_empty(AST_NUMBER_LITERAL);
    node->value = value;
    return node;
}

ASTNode* ast_create_string_literal(const char* value) {
    ASTNode* node = ast_create_empty(AST_STRING_LITERAL);
    node->value = value;
    return node;
}