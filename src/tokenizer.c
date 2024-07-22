#include <stdio.h>
#include <regex.h>
#include <assert.h>
#include <stdlib.h>
#include <regexp.h>
#include <tokenizer.h>
#include <slibs/slibs.h>

const char* TokenTypeText[] = {
    "l_paren",
    "r_paren",
    "number",
    "name",
    "string"
};

void tokenize(char* input, TokenVec* tokens) {
    regex_t name = regex_create("[a-z_]", REG_ICASE);
    regex_t number = regex_create("[0-9]", 0);
    regex_t string = regex_create("\"", 0);
    regex_t whitespace = regex_create("[ \n]", 0);
    sl_string collected = {0};

    char c = *input;
    while (c != '\0') {
        if (match_char(name, c)) {
            collected = collect_until_no_match(name, &input);
            sl_vec_push(*tokens, token_create(sl_c_str(collected), TOKEN_NAME));
        } else if (match_char(number, c)) {
            collected = collect_until_no_match(number, &input);
            sl_vec_push(*tokens, token_create(sl_c_str(collected), TOKEN_NUMBER));
        } else if (c == '(') {
            sl_vec_push(*tokens, token_create("(", TOKEN_LPAREN));
            input++;
        } else if (c == ')') {
            sl_vec_push(*tokens, token_create(")", TOKEN_RPAREN));
            input++;
        } else if (match_char(whitespace, c)) {
            input++;
        } else if (match_char(string, c)) {
            regex_step(&input, &c);
            collected = collect_until_match_escapable(string, &input);
            sl_vec_push(*tokens, token_create(sl_c_str(collected), TOKEN_STRING));
            input++;
        } else {
            printf("%c: no match\n", c);
            exit(-1);
        }

        c = *input;
    }

    regfree(&name);
    regfree(&number);
    regfree(&string);
    regfree(&whitespace);
}

Token* token_create(char* value, TokenType type) {
    Token* new_token = malloc(sizeof(Token));
    new_token->value = value;
    new_token->type = type;

    return new_token;
}

void tokens_print(TokenVec tokens) {
    for(sl_vec_it(token, tokens)) {
        printf("%s: %s\n", TokenTypeText[(*token)->type], (*token)->value);
    }
}