#ifndef LEXER
#define LEXER
// #include <cstddef>
#include <sys/types.h>
#pragma once
#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
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

typedef struct TokenContainer {
    size_t length;
    Token* tokens;
}token_container;

char* init_buf(size_t i_pos, size_t end_pos);

size_t is_header(size_t content_len, size_t c_pos, char* content);

size_t is_cmd( size_t content_len, size_t c_pos, char* content);

size_t is_inline_eq( size_t content_len, size_t c_pos, char* content);

void compile_inline(char *content, size_t position, size_t len_content, Token *t, char* buffer);

void compile_header(char *content, Token *t, char* buffer, size_t initial_pos, size_t end_pos);

void compile_text(char *content, Token *t,  size_t *end_pos, size_t len_content);

void compile_command(char *content, Token *t, char* buffer, size_t initial_pos, size_t end_pos);

void lex_content(char *content, token_container *container);

#endif