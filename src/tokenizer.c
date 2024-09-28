#include <assert.h>
#include <regex.h>
#include <regexp.h>
#include <slibs/slibs.h>
#include <stdio.h>
#include <stdlib.h>
#include <tokenizer.h>

const char *TokenTypeText[] = {"none",   "l_paren", "r_paren",
                               "number", "name",    "string"};

void tokenize(char *input, TokenVec *tokens) {
  regex_t name = regex_create("[a-z_]", REG_ICASE);
  regex_t number = regex_create("[0-9]", 0);
  regex_t string = regex_create("\"", 0);
  regex_t whitespace = regex_create("[ \n]", 0);
  sl_string collected = {0};

  char c = *input;
  while (c != '\0') {
    Token token = {0};

    if (match_char(name, c)) {
      collected = collect_until_no_match(name, &input);
      token.value = sl_c_str(collected);
      token.type = TOKEN_NAME;
    } else if (match_char(number, c)) {
      collected = collect_until_no_match(number, &input);
      token.value = sl_c_str(collected);
      token.type = TOKEN_NUMBER;
    } else if (c == '(') {
      token.value = "(";
      token.type = TOKEN_LPAREN;
      input++;
    } else if (c == ')') {
      token.value = ")";
      token.type = TOKEN_RPAREN;
      input++;
    } else if (match_char(whitespace, c)) {
      input++;
    } else if (match_char(string, c)) {
      regex_step(&input, &c);
      collected = collect_until_match_escapable(string, &input);
      token.value = sl_c_str(collected);
      token.type = TOKEN_STRING;
      input++;
    } else {
      printf("%c: no match\n", c);
      exit(-1);
    }

    if (token.type != TOKEN_NONE) {
      sl_vec_push(*tokens, token);
    }

    c = *input;
  }

  regfree(&name);
  regfree(&number);
  regfree(&string);
  regfree(&whitespace);
}

void tokens_print(TokenVec tokens) {
  for (sl_vec_it(token, tokens)) {
    printf("%s: %s\n", TokenTypeText[token->type], token->value);
  }
}
