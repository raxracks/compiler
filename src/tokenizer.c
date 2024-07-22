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

Token* tokenize(char* input) {
    regex_t name = regex_create("[a-z_]", REG_ICASE);
    regex_t number = regex_create("[0-9]", 0);
    regex_t string = regex_create("\"", 0);
    regex_t whitespace = regex_create("[ \n]", 0);
    Token* root = NULL;
    sl_string collected = {0};

    char c = *input;
    while (c != '\0') {
        if (match_char(name, c)) {
            collected = collect_until_no_match(name, &input);
            root = token_create(sl_c_str(collected), TOKEN_NAME, root);
        } else if (match_char(number, c)) {
            collected = collect_until_no_match(number, &input);
            root = token_create(sl_c_str(collected), TOKEN_NUMBER, root);
        } else if (c == '(') {
            root = token_create("(", TOKEN_LPAREN, root);
            input++;
        } else if (c == ')') {
            root = token_create(")", TOKEN_RPAREN, root);
            input++;
        } else if (match_char(whitespace, c)) {
            input++;
        } else if (match_char(string, c)) {
            regex_step(&input, &c);
            collected = collect_until_match_escapable(string, &input);
            root = token_create(sl_c_str(collected), TOKEN_STRING, root);
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
    return root;
}

Token* token_create(char* value, TokenType type, Token* root) {
    Token* new_token = calloc(1, sizeof(Token));
    new_token->value = value;
    new_token->type = type;

    return token_append(root, new_token);;
}

Token* token_append(Token* root, Token* new_token) {
    if (!root) return new_token;
    Token* current = root;
    while (current->next) {
        current = current->next;
    }
    current->next = new_token;
    return root;
}

void tokens_print(Token* root) {
    while(root != NULL) {
        printf("%s: %s\n", TokenTypeText[root->type], root->value);
        root = root->next;
    }
}