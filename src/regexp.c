#include <stdio.h>
#include <stdlib.h>
#include <regexp.h>

int regex_exec_char(const regex_t *preg, const char c, size_t nmatch, regmatch_t pmatch[], int eflags) {
    char str[2] = {c, '\0'};

    return regexec(preg, str, nmatch, pmatch, eflags);
}

void regex_step(char** input, char* c) {
    (*input)++;
    *c = **input;
}

regex_t regex_create(const char* pattern, int flags) {
    regex_t regex;
    int ret = regcomp(&regex, pattern, flags);
    if(ret) {
        char msgbuf[100];
        regerror(ret, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", msgbuf);
        exit(-1);
    }

    return regex;
}

int match_char(regex_t regex, const char c) {
    return regex_exec_char(&regex, c, 0, NULL, 0) != REG_NOMATCH;
}

sl_string collect_until(match_func matcher, regex_t regex, char** input) {
    sl_string collected = {0};
    char c = **input;

    while (matcher(regex, c, input)) {
        sl_vec_push(collected, c);
        regex_step(input, &c);
    }

    return collected;
}

int not_match_char(regex_t regex, char c, char** _) {
    return !match_char(regex, c);
}

int match_char_matcher(regex_t regex, char c, char** _) {
    return match_char(regex, c);
}

int not_match_char_escapable(regex_t regex, char c, char** input) {
    return !match_char(regex, c) || *((*input) - 1) == '\\';
}

int match_char_escapable(regex_t regex, char c, char** input) {
    return match_char(regex, c) || *(*input) == '\\';
}

sl_string collect_until_match(regex_t regex, char** input) {
    return collect_until(not_match_char, regex, input);
}

sl_string collect_until_no_match(regex_t regex, char** input) {
    return collect_until(match_char_matcher, regex, input);
}

sl_string collect_until_match_escapable(regex_t regex, char** input) {
    return collect_until(not_match_char_escapable, regex, input);
}

sl_string collect_until_no_match_escapable(regex_t regex, char** input) {
    return collect_until(match_char_escapable, regex, input);
}