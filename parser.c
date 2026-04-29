#include "parse.h"
#include <stdbool.h>
// #include <memory>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>



bool is_something(char c){

}

bool is_inline(char c){
    // *** Second bang proves that we are in fact working with a command
    switch(c){
        case '$': {
            return true;
        }case ',': {
            return false;
            break;
        }
        case '.': {
            return false;
            break;
        }
        case '\n' : {
            return false;
        }
        default:
            return false;
    }
}

bool is_cmd(char c){
    // *** Second bang proves that we are in fact working with a command
    switch(c){
        case '!': {
            return true;
        }case ',': {
            return false;
            break;
        }
        case '.': {
            return false;
            break;
        }
        case '\n' : {
            return false;
        }
        default:
            return false;
    }
}

bool is_header(char c){
    switch (c){
        case '}':{
            return true;
        }
        case '.':
        default:{
            return false;
        }
    }
}

char* init_buf(size_t len_content, size_t *pos){
    size_t len_buf = len_content-*pos;
    char *buf = (char *)malloc(len_buf);
    // if(buf) {
    //     buf[len_buf] = '\0';
    // }
    return buf;
}

void compile_inline(char *content, size_t *c_position, size_t len_content, Token *t, char* buf){
    char inline_char = '$';
    bool inline_eq;
    char *buffer =init_buf(len_content, c_position);
    printf("[DEBUG] Initial buffer size:");
    size_t i = 0;

    // *** Starting ahead of bang
    *c_position+=1;
    // printf("c_pos: ")
    while(*c_position < len_content){
        ;
    }

}

void compile_header(char *content, size_t *c_position, size_t len_content, Token *t, char* buffer){
    char inline_char = '}';
    size_t i = 0;
    // *** check char after # should be } if header else
    *c_position+=1;
    
    if(content[*c_position]=='}'){
        while(*c_position < len_content){
            ;
        }
    }
}
    

void compile_text(char *content, size_t *position, size_t len_content, Token *t){

}


// @ params uses the content of the full text
//  current position in the text and the length of the full text
void compile_command(char *content, size_t *c_position, size_t len_content, Token *t, char* buffer){
    char bang = '!';
    size_t i = 0;
    *c_position = *c_position+1;
    while(*c_position < len_content){
        ;
    }
};

// @ brief a lexing function that identifies individual characters and compiles them using subsequent commands
// each compile command does parsing as well as tokenizing
// @ param content: the full content of the file/text
void lex_content(char *content){
    size_t len_content, pos;
    len_content = strlen(content);

    for(pos = 0; pos<len_content; pos++){
        Token t;
        switch (content[pos]) {
            case '#':
            {
                printf("Possible header found\n");
                break;
            }
            case '$':
            {
                // printf(GREEN "Possible inline command found\n" RESET);
                // char* buf = init_buf(len_content,&pos);
                // if(compile_inline(content, &pos, len_content, &t))
                // printf("Block equation data: %s\n\n", t.data);
                // break;
            }
            case '!':
            {
                
                // first check if cmd
                bool command = is_cmd(content[pos]);
                if(command){
                    printf(GREEN "Command Token found\n"RESET);
                    char* buf = init_buf(len_content,&pos); 
                }else {
                    // default: compile text??
                    ;
                }
                
               
                printf("Block equation data: %s\n\n", t.data);
                // break;
            }
            default:
            {
                char* buf = init_buf(len_content,&pos);
                while(content[pos]!=' '){
                    buf+= content[pos];
                }
                printf("buffer: %s\n", buf);
                // printf("Normal \n");
            }
        }
    }
}
