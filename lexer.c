#include "lexer.h"
#include <stddef.h>
#include <stdint.h>


size_t is_inline_eq(size_t content_len, size_t c_pos, char* content){
    printf("[DEBUG] Checking if command\n");
    // *** Second bang proves that we are in fact working with a command
    size_t i = c_pos + 1;  // Start after current position
    while (i < content_len) {
        char ch = content[i];
        
        if (ch == '$') {
            return i;
        } else if (ch == ',' || ch == '.') {
            return SIZE_MAX;
        }       
        i++;
    }
    
    return SIZE_MAX;
}

size_t is_cmd(size_t content_len, size_t c_pos, char* content){
    printf("[DEBUG] Checking if command\n");
    // *** Second bang proves that we are in fact working with a command
    size_t i = c_pos + 1;  // Start after current position
    while (i < content_len) {
        char ch = content[i];
        
        if (ch == '!') {
            return i;
        } else if (ch == ',' || ch == '.') {
            return SIZE_MAX;
        }       
        i++;
    }
    
    return SIZE_MAX;
}

size_t is_header(size_t content_len, size_t c_pos, char* content){
    printf("[DEBUG] Checking if command\n");
    // *** Second bang proves that we are in fact working with a command
    size_t i = c_pos + 1;  // Start after current position
    while (i < content_len) {
        char ch = content[i];
        
        if (ch == '}') {
            return i;
        } else if (ch == ',' || ch == '.' || ch == '\n') {
            return SIZE_MAX;
        }       
        i++;
    }
    
    return SIZE_MAX;
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
    printf("[DEBUG] About to free buffer at %p\n", buffer);
    printf("t.data: %p, buf: %p\n", t->data, buffer);                    
    t->data = malloc(strlen(buffer)+1);
    strcpy(t->data,buffer);
    free(buffer);
    printf("[DEBUG] Freed buffer\n");
}
    

void compile_text(char *content, Token *t,  size_t *c_pos, size_t len_content){
    printf("\t\t\t[DEBUG] In function compile_text()\n");
    size_t buffer_indx = 0;
    size_t initial_pos = *c_pos;    
    while(*c_pos < len_content){
        if(content[*c_pos] == ' '){
            break;
        }
        (*c_pos)++;
    }
    size_t e_pos = *c_pos;
    char* buffer = init_buf(initial_pos, e_pos);
    while(initial_pos != *c_pos){
        buffer[buffer_indx] = content[initial_pos];
        // printf("Current buffer: %s\n", buffer);
        initial_pos+=1;
        buffer_indx++;
    }
    t->data = malloc(strlen(buffer)+1);
    strcpy(t->data,buffer);
    printf("buffer: %s\n\n", buffer);
    printf("t.data: %p (%s), buf: %p\n", t->data, t->data, buffer);
    printf("[DEBUG] About to free buffer at %p\n", buffer);
    free(buffer);
    printf("[DEBUG] Freed buffer\n");
    t->attrib = TEXT;
}

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
    printf("Buffer: %s\n", buffer);
    printf("[DEBUG] About to free buffer at %p\n", buffer);
    printf("t.data: %p(p) %s(s), buf: %p\n", t->data, t->data, buffer);
    t->data = malloc(strlen(buffer)+1); 
    strcpy(t->data,buffer);
    free(buffer);
    printf("[DEBUG] Freed buffer\n");
}

// @ brief a lexing function that identifies individual characters and compiles them using subsequent commands
// each compile command does parsing as well as tokenizing
// @ param content: the full content of the file/text
void lex_content(char *content, token_container *container){
    size_t len_content, pos;
    len_content = strlen(content);
    size_t n_tokens = 0; 
    container->tokens = (malloc( len_content * sizeof(Token)));
    // Token token_array[len_content/2];
    size_t buffer_indx = 0;
    
    for (pos = 0; pos < len_content; pos++) {
        n_tokens++;
        char c = content[pos];
        printf("%d\n", c);

        if (c == '\n') {
            Token t;
            printf("\t\t\t\t\tFOUND NEW LINE\n");
            t.data = "\\n";
            t.attrib = NEW_LINE;

            container->tokens[buffer_indx] = t;
            buffer_indx++;
        }
        else if (c == '#') {
            Token t;
            printf("[DEBUG] Possible header found\n");

        }
        else if (c == '$') {
            Token t;
        }
        else if (c == '!') {
            Token t;
        }
        else {
            if (content[pos] == ' ') {
                continue;
            }
        }
    }


    container->tokens = realloc(container->tokens,(n_tokens+1) * sizeof(Token));
    container->length = n_tokens+1;
    container->tokens[n_tokens].data = malloc(1);
    container->tokens[n_tokens].data[0] = '\0';
    container->tokens[n_tokens].attrib = TEXT;
    printf("container[3]: %s\n", container->tokens[1].data);
    // for(size_t i=0;i<n_tokens+1;i++){
    //     switch (container->tokens[i].attrib) {
    //         case HEADER:
    //         {
    //             printf("HEADER(%s)\n", container->tokens[i].data);
    //             break;
    //         }
    //         case INLINE_EQ:{
    //             printf("INLINE_EQ(%s)\n", container->tokens[i].data);
    //             break;
    //         }
    //         case BLOCK_EQ:{
    //             printf("BLOCK_EQ(%s)\n", container->tokens[i].data);
    //             break;
    //         }
    //         case NEW_LINE:{
    //             printf("NEW_LINE(%s)\n", container->tokens[i].data);
    //             break;
    //         }
    //         default :{
    //             printf("TEXT(%s)\n", container->tokens[i].data);
    //             break;
    //         }
            
    //     }
    // }
}
