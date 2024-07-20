#include <regex.h>
#include <slibs/slibs.h>

#ifndef __REGEXP_H__
#define __REGEXP_H__

typedef int (*match_func)(regex_t, char, char**);

regex_t regex_create(const char* pattern, int flags);
int match_char(regex_t regex, char c);
sl_string collect_until(match_func matcher, regex_t regex, char** input);
sl_string collect_until_match(regex_t regex, char** input);
sl_string collect_until_no_match(regex_t regex, char** input);
sl_string collect_until_match_escapable(regex_t regex, char** input);
sl_string collect_until_no_match_escapable(regex_t regex, char** input);
void regex_step(char** input, char* c);

#endif