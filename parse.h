#ifndef PARSE
#define PARSE
#pragma once
#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
// #include <cstdio>
#include "string.h"

#define GREEN "\x1b[33m"
#define RESET "\x1b[0m"

enum TOKEN_TYPE {
    HEADER = '}',
    BLOCK_EQ = '!',
    INLINE_EQ = '$',
    TEXT = ' ',
    NEW_LINE= '\n'
};

typedef struct Token {
    enum TOKEN_TYPE attrib;
    char *data;
}Token;

bool is_header(char c);

bool is_cmd(char c);

bool is_inline(char c);

void compile_inline(char *content, size_t *position, size_t len_content, Token *t, char* buffer);

void compile_header(char *content, size_t *position, size_t len_content, Token *t, char* buffer);

void compile_text(char *content, size_t *position, size_t len_content, Token *t);

void compile_command(char *content, size_t *position, size_t len_content, Token *t, char* buffer);

void lex_content(char *content);

#endif