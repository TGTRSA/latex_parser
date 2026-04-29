#include "parse.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <memory>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>


bool in_inline(size_t content_len, size_t *c_pos, char* content){
    // *** Second bang proves that we are in fact working with a command
    while (*c_pos<content_len) {
        switch(content[*c_pos]){
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
               ;
        }
        *c_pos = *c_pos+1;
    }
    return false;
}

bool is_cmd(size_t content_len, size_t *c_pos, char* content){
    printf("[DEBUG] Checking if command\n");
    // *** Second bang proves that we are in fact working with a command
    *c_pos = *c_pos+1;
    while(*c_pos<content_len){       
        switch(content[*c_pos]){
            case '!': {
                return true;
            }case ',': {
                // return false;
                break;
            }
            case '.': {
                // return false;
                break;
            }
            case '\n' : {
                // return false;
            }
            default:
                // return false;
                ;
        }
        *c_pos = *c_pos + 1;
    }
    return false;
}

bool is_header(size_t content_len, size_t *c_pos, char* content){
    *c_pos = *c_pos + 1;
    while(content[*c_pos]){
        switch (content[*c_pos]){
            case '}':{
                return true;
            }
            case '.':
            default:{
                return false;
            }
        }
    }
    return false;
}

char* init_buf(size_t i_pos, size_t *pos){
    // creating the buffer of the size between beginning and end of command: higher-lower bc we are using unsigned ints
    size_t len_buf = *pos - i_pos;
    printf("[DEBUG] %zu - %zu\n", *pos, i_pos);
    printf("\tCreating buffer of size: %zu\n", len_buf+1);
    char *buf = (char *)malloc(len_buf+1);
    buf[len_buf+1] = '\0';
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
void compile_command(char *content, Token *t, char* buffer, size_t initial_pos, size_t *end_pos){
    char bang = '!';
    // size_t content_pos = initial_pos+1;
    initial_pos++;
    size_t buffer_indx = 0;
    while(initial_pos != *end_pos){
        buffer[buffer_indx] = content[initial_pos];
        printf("Current buffer: %s\n", buffer);
        initial_pos+=1;
        buffer_indx++;
    }
    strcpy(t->data,buffer);
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
                size_t initial_pos = pos;
                bool command = is_cmd(len_content, &pos, content);
                if(command){
                    printf(GREEN "Command Token found\n"RESET);
                    printf("Inital pos: %zu\n\tNew pos: %zu\n", initial_pos, pos);
                    char* buf = init_buf(initial_pos,&pos); 
                    compile_command(content,&t,buf,  initial_pos, &pos);
                    free(buf);
                    printf("Freeing buffer\n");
                    pos = pos +1;
                }else {
                    // default: compile text??
                    ;
                }               
                printf("Block equation data: %s\n\n", t.data);
                // break;
            }
            default:
            {
                // char* buf = init_buf(len_content,&pos);
                // while(content[pos]!=' '){
                //     buf+= content[pos];
                // }
                // printf("buffer: %s\n", buf);
                // printf("Normal \n");
                ;
            }
        }
    }
}
