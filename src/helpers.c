#include <helpers.h>
#include <string.h>
#include <stdlib.h>

char* gen_ident(int indent) {
    char* text = malloc(sizeof(char) * (indent + 1));
    memset(text, ' ', indent);
    text[indent] = '\0';
    return text;
}