#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

extern const char *TokenTypeText[];

typedef enum TokenType {
  TOKEN_NONE,
  TOKEN_LPAREN,
  TOKEN_RPAREN,
  TOKEN_NUMBER,
  TOKEN_NAME,
  TOKEN_STRING
} TokenType;

typedef struct Token {
  char *value;
  TokenType type;
} Token;

typedef sl_vec(Token) TokenVec;

void tokenize(char *input, TokenVec *tokens);

Token *token_create(char *value, TokenType type);
void tokens_print(TokenVec tokens);

#endif
