#include <slibs/slibs.h>
#include <tokenizer.h>

#ifndef __AST_H__
#define __AST_H__

extern const char* ASTTypeText[];

typedef enum ASTType {
    AST_PROGRAM,
    AST_CALL_EXPRESSION,
    AST_NUMBER_LITERAL,
    AST_STRING_LITERAL
} ASTType;

typedef sl_vec(struct ASTNode*) ASTVec;

typedef struct ASTNode {
    ASTType type;
    const char* name;
    const char* value;

    ASTVec body;
    ASTVec params;
} ASTNode;

ASTNode* ast_parse(TokenVec* token);
ASTNode* ast_walk(TokenVec* token);
void ast_print(ASTNode* node, int indent);
ASTNode* ast_create_empty(ASTType type);
ASTNode* ast_create_program(ASTVec body);
ASTNode* ast_create_call_expression(const char* name, ASTVec params);
ASTNode* ast_create_number_literal(const char* value);
ASTNode* ast_create_string_literal(const char* value);

#endif