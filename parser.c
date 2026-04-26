#include "parse.h"
// #include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

// @ params uses the content of the full text
//  current position in the text and the length of the full text
void compile_command(char *content, size_t *c_position, size_t len_content, Token *t){
    char bang = '!';

    // *** allocating the entire rest of the file size
    char *buffer = (char *)malloc(len_content-*c_position);
    printf("Initial buffer size: %zu\n", len_content-*c_position);
    size_t i = 0;

    // *** Starting ahead of bang
    *c_position+=1;
    // printf("c_pos: ")
    while(*c_position < len_content){
        
        // printf("[DEBUG]Current buffer: %s at position %zu\n", buffer, *c_position);
        bool command = is_cmd(content[*c_position]);
        if(command){
            // resizing the buffer to be only the size of the content
            printf("Number of characters %zu\n", i);
            printf("Size buffer should be %zu\n", i);

            buffer = realloc(buffer,i + 1);
            buffer[i] = '\0';
            if(!buffer) {printf("Error reallocating buffer\n"); free(buffer); exit(1);}

            printf("[DEBUG] New buffer size: %zu\n",strlen(buffer));
            printf("\t[DEBUG] Buffer after reallocation: %s\n[DEBUG] Writing %zu into buffer(%zu bytes)\n",buffer,i, strlen(buffer));
            
            strcpy(t->data ,buffer);
            t->attrib = BLOCK_EQ;
            *c_position=*c_position+1;
            break;
        }
        // feeding each char to the buffer
        buffer[i] = content[*c_position];
        *c_position=*c_position+1;
        i++;
    }
    printf("buffer: %s\n", buffer);
    free(buffer);
    printf("Freeing buffer\n");
};

// @ brief a lexing function that identifies individual characters and compiles them using subsequent commands
// each compile command does parsing as well as tokenizing 
// @ param content: the full content of the file/text
void lex_content(char *content){
    size_t len_content, i;
    len_content = strlen(content);

    for(i = 0; i<len_content; i++){
        Token t;
        switch (content[i]) {
            case '#':
            {
                printf("Possible header found\n");
                break;
            }
            case '$':
            {
                printf("Possible inline command found\n");
                break;
            }
            case '!':
            {
                printf("Command Token found\n");
                compile_command(content,&i,len_content, &t);
                
                printf("Token data: %s\n", t.data);
                break;
            }
            
            default:
            {
                // printf("Normal char\n");
            }
        }
    }
}
