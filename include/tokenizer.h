#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

extern const char* TokenTypeText[];

typedef enum TokenType {
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_NUMBER,
    TOKEN_NAME,
    TOKEN_STRING
} TokenType;

typedef struct Token {
    char* value;
    TokenType type;
    struct Token* next;
} Token;

Token* tokenize(char* input);

Token* token_create(char* value, TokenType type, Token* root);
Token* token_append(Token* root, Token* new_token);

#endif