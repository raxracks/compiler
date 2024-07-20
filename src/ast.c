#include <ast.h>

const char* ASTTypeText[] = {
    "Program",
    "CallExpression",
    "NumberLiteral",
    "StringLiteral"
};

ASTNode* ast_parse(Token** token) {
    ASTVec body = { 0 };

    while((*token) != NULL) {
        sl_vec_push(body, ast_walk(token));
    }

    return ast_create_program(body);
}

ASTNode* ast_walk(Token** token) {
    if((*token)->type == TOKEN_NUMBER) {
        ASTNode* number = ast_create_number_literal((*token)->value);
        ast_step(token);
        return number;
    }

    if((*token)->type == TOKEN_STRING) {
        ASTNode* string = ast_create_string_literal((*token)->value);
        ast_step(token);
        return string;
    }

    if((*token)->type == TOKEN_LPAREN) { // Call expression
        ast_step(token);
        const char* name = (*token)->value;
        ASTVec params = { 0 };

        ast_step(token);

        while((*token)->type != TOKEN_RPAREN) {
            sl_vec_push(params, ast_walk(token));
        }

        ast_step(token);

        return ast_create_call_expression(name, params);
    }

    return NULL;
}

void ast_step(Token** token) {
    (*token) = (*token)->next;
}

char* gen_ident(int indent) {
    char* text = malloc(sizeof(char) * (indent + 1));
    memset(text, ' ', indent);
    text[indent] = '\0';
    return text;
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