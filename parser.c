#include "parse.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
// #include <memory>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

ssize_t is_inline_eq(size_t content_len, size_t c_pos, char* content){
    printf("[DEBUG] Checking if command\n");
    // *** Second bang proves that we are in fact working with a command
    size_t i = c_pos + 1;  // Start after current position
    while (i < content_len) {
        char ch = content[i];
        
        if (ch == '$') {
            return i;
        } else if (ch == ',' || ch == '.' || ch == '\n') {
            return -1;
        }       
        i++;
    }
    
    return -1;
}

ssize_t is_cmd(size_t content_len, size_t c_pos, char* content){
    printf("[DEBUG] Checking if command\n");
    // *** Second bang proves that we are in fact working with a command
    size_t i = c_pos + 1;  // Start after current position
    while (i < content_len) {
        char ch = content[i];
        
        if (ch == '!') {
            return i;
        } else if (ch == ',' || ch == '.' || ch == '\n') {
            return -1;
        }       
        i++;
    }
    
    return -1;
}

ssize_t is_header(size_t content_len, size_t c_pos, char* content){
    printf("[DEBUG] Checking if command\n");
    // *** Second bang proves that we are in fact working with a command
    size_t i = c_pos + 1;  // Start after current position
    while (i < content_len) {
        char ch = content[i];
        
        if (ch == '}') {
            return i;
        } else if (ch == ',' || ch == '.' || ch == '\n') {
            return -1;
        }       
        i++;
    }
    
    return -1;
}


char* init_buf(size_t i_pos, size_t end_pos){
    // creating the buffer of the size between beginning and end of command: higher-lower bc we are using unsigned ints
    size_t len_buf = end_pos - i_pos;
    printf("[DEBUG] %zu - %zu\n", end_pos, i_pos);
    printf("\tCreating buffer of size: %zu\n", len_buf+1);
    char *buf = (char *)malloc(len_buf+1);
    buf[len_buf] = '\0';
    return buf;
}

void compile_inline(char *content, size_t c_position, size_t len_content, Token *t, char* buf){
    char inline_char = '$';
    bool inline_eq;
    char *buffer =init_buf(len_content, c_position);
    printf("[DEBUG] Initial buffer size:");
    size_t i = 0;

    // *** Starting ahead of bang
    c_position+=1;
    // printf("c_pos: ")
    while(c_position < len_content){
        ;
    }

}

void compile_header(char *content, Token *t, char* buffer, size_t initial_pos, size_t end_pos){
    // size_t content_pos = initial_pos+1;
    initial_pos++;
    size_t buffer_indx = 0;
    while(initial_pos<end_pos){
        if(content[initial_pos]=='{'){
            break;
        }else{
            initial_pos++;
        }
    }
    initial_pos+=1;
    while(initial_pos != end_pos){
        buffer[buffer_indx] = content[initial_pos];
        // printf("Current buffer: %s\n", buffer);
        initial_pos+=1;
        buffer_indx++;
    }
    strcpy(t->data,buffer);
}
    

void compile_text(char *content, Token *t, char* buffer, size_t initial_pos, size_t end_pos){
    size_t buffer_indx = 0;
    while(initial_pos != end_pos){
        buffer[buffer_indx] = content[initial_pos];
        // printf("Current buffer: %s\n", buffer);
        initial_pos+=1;
        buffer_indx++;
    }
    strcpy(t->data,buffer);
    printf("buffer: %s\n\n", buffer);
    printf("t.data: %p, buf: %p\n", t->data, buffer);
    printf("[DEBUG] About to free buffer at %p\n", buffer);
    free(buffer);
    printf("[DEBUG] Freed buffer\n");
    t->attrib = TEXT;
};

// @ params uses the content of the full text
//  current position in the text and the length of the full text
void compile_command(char *content, Token *t, char* buffer, size_t initial_pos, size_t end_pos){
    initial_pos++;
    size_t buffer_indx = 0;
    while(initial_pos < end_pos){
        buffer[buffer_indx] = content[initial_pos];
        // printf("Current buffer: %s\n", buffer);
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
    size_t n_tokens = 0;
    token_container container; 
    container.tokens = (malloc( len_content * sizeof(Token)));
    // Token token_array[len_content/2];
    size_t buffer_indx = 0;
    
    for(pos = 0; pos<len_content; pos++){
        n_tokens++;
        switch (content[pos]) {
            case '#':
            {
                Token t;
                printf("[DEBUG] Possible header found\n");
                ssize_t header_end_pos = is_header(len_content,pos,content);
                if(header_end_pos>=0){

                    char* buf = init_buf(pos,header_end_pos);
                    printf("[DEBUG] Initial pos %zu: \n\tNew pos: %zu\n", pos, header_end_pos);

                    compile_header(content, &t, buf,pos,header_end_pos);

                    printf("\t[DEBUG]End pos content[%zu]: %c\n\n", header_end_pos, content[header_end_pos]);

                    printf("[DEBUG] About to free buffer at %p\n", buf);
                    printf("t.data: %p, buf: %p\n", t.data, buf);
                    free(buf);
                    printf("[DEBUG] Freed buffer\n");
                    t.attrib = HEADER;         
                    if(header_end_pos!=len_content && len_content != header_end_pos +1 ){
                        pos = header_end_pos+1;
                    }
                }else{
                    ;
                }
                container.tokens[buffer_indx] = t;
                buffer_indx = buffer_indx + 1;
                break;
            }
            case '$':
            {
                Token t;
                ssize_t end_pos  = is_inline_eq(len_content,pos, content);
                printf("\t[DEBUG]\tcontent[%zu]: %c\n", pos, content[pos]);

                if(end_pos>=0){    

                    printf(GREEN "Command Token found\n"RESET);
                    printf("Initial pos %zu: \n\tNew pos: %zu\n", pos, end_pos);

                    char* buf = init_buf(pos,end_pos); 
                    compile_command(content,&t,buf,  pos, end_pos);
                    printf("[DEBUG] About to free buffer at %p\n", buf);
                    printf("t.data: %p, buf: %p\n", t.data, buf);                    
                    free(buf);
                    printf("[DEBUG] Freed buffer\n");

                    printf("\t[DEBUG]End pos content[%zu]: %c\n", end_pos, content[end_pos]);

                    t.attrib = INLINE_EQ;
                    
                    if(end_pos != len_content && end_pos + 1 != len_content){
                        pos = end_pos + 1;
                    }
                    // Should print empty space or random char
                }else {
                    ;
                }       
                printf("Equation data: %s\n\n", t.data);
                // container[buffer_indx] = t;
                // buffer_indx = buffer_indx + 1;                
                break;
            }
            case '!':
            {
                Token t;
                ssize_t end_pos  = is_cmd(len_content,pos, content);
                printf("\t[DEBUG]\tcontent[%zu]: %c\n", pos, content[pos]);
                if(end_pos>=0){    

                    printf(GREEN "Command Token found\n"RESET);
                    printf("Initial pos %zu: \n\tNew pos: %zu\n", pos, end_pos);

                    char* buf = init_buf(pos,end_pos); 
                    compile_command(content,&t,buf,  pos, end_pos);
                    printf("[DEBUG] About to free buffer at %p\n", buf);
                    printf("t.data: %p, buf: %p\n", t.data, buf);
                    
                    free(buf);
                
                    printf("[DEBUG] Freed buffer\n");
                    printf("\t[DEBUG]End pos content[%zu]: %c\n", end_pos, content[end_pos]);

                    t.attrib = BLOCK_EQ;
                    
                    if(end_pos != len_content && end_pos + 1 != len_content){
                        pos = end_pos + 1;
                    }
                    // Should print empty space or random char
                }else {
                    printf("[DEBUG] Not a header at %zu \n\n", pos);
                }       
                container.tokens[buffer_indx] = t;
                buffer_indx = buffer_indx + 1;

                printf("Block equation data: %s\n\n", t.data);
                break;
            }
            case '\n':{
                break;
            }
            default:
            {
                ;

            }
        }
    }

    container.tokens = realloc(container.tokens,(n_tokens+1) * sizeof(Token));

    container.tokens[n_tokens] = (struct Token){.data = "\0", .attrib=TEXT};
    printf("container[1]: %s\n", container.tokens[1].data);
    // int i;
    // for(i=0;i<n_tokens;i++){
    //     printf("container[%i]: %s\n", i, container[i].data);
    // }
    // for(i=0;i<n_tokens+1;i++){
    //     switch (container[i].attrib) {
    //         case HEADER:
    //         {
    //             printf("HEADER(%s)", container[i].data);
    //             break;
    //         }
    //         case INLINE_EQ:{
    //             printf("INLINE_EQ(%s)", container[i].data);
    //             break;
    //         }
    //         case BLOCK_EQ:{
    //             printf("BLOCK_EQ(%s)", container[i].data);
    //             break;
    //         }
    //         case NEW_LINE:{
    //             printf("NEW_LINE(%s)", container[i].data);
    //             break;
    //         }
    //         default :{
    //             printf("TEXT(%s)", container[i].data);
    //             break;
    //         }
            
    //     }
    // }
}
