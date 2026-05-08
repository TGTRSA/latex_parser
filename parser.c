#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* latex_code = "\\documentclass{article}\n"
                    "\\usepackage[utf8]{inputenc}\n"
                    "\\usepackage{asmath}\n"
                    "\\usepackage{tikz}\n"
                    "\\usepackage{geometry}";

const char* begin_doc  = "\n\\begin{document}\n";
const char* end_doc    = "\n\\end{document}\n";
bool header_written=false;

void write_header(Token *t) {
    printf("%s\n", t->data);
    
    char* usepackage = "\n\\usepackage{}";
    // char* buf = (char *)  malloc(  sizeof(char) * strlen(latex_code));
    // size_t doc_opening_len = sizeof(char) * strlen(usepackage) + strlen(t->data) + strlen(latex_code);
    // char* full_tex = (char *) (malloc(doc_opening_len )); 
    char* usepackge_str = (char *) malloc(sizeof(char) * strlen(usepackage) + 1);
    size_t len_token = strlen(t->data);
    // char* usepackage_buffer = (char *) malloc(sizeof(char)*(strlen(usepackage) + len_token ) + 1);
    
    // taking the latex content and putting it into a buffer that can handle it 
    // then creating the psckage and appending it to the buffer
    // strcpy(full_tex,latex_code);
    // free(latex_code);
    // sprintf(usepackage_buffer,  "\\usepackage{%s}", t->data);
    // strcat(full_tex,usepackage_buffer);

    // latex_code = (char *) malloc(sizeof(char) * strlen(full_tex) + 1);
    // printf("[DEBUG] Usepackage buffer: %s\n", usepackage_buffer);
    // free(usepackage_buffer);
    // latex_code = full_tex;
    // printf("%s\n", latex_code);

    // free(full_tex);
}

void write_token(Token *t, char* doc_content, char* buffer){

}

void compile_tex(token_container *container){
    char* doc_cont = (char * ) malloc(sizeof(char)  * strlen(latex_code) +  1);
    strcpy(doc_cont, latex_code);
    size_t len_tracker = strlen(doc_cont);
    doc_cont[strlen(latex_code)] = '\0';
    
    printf("\n[DEBUG] In parser.h:\n");
    printf("[DEBUF] Original length of doc_content buffer: %zu\n", sizeof(doc_cont));
    printf("[DEBUG] Len of token container: %zu\n", container->length);
    
    size_t i;    
    for(i=0;i<container->length;i++){
        Token t = container->tokens[i] ;
        if(t.attrib!=HEADER && header_written==false){
            header_written=true;
        }
        switch (t.attrib) {
            case HEADER:
            {
                printf("HEADER(%s)\n",t.data);
                write_header( &t);
                break;
            }
            case INLINE_EQ:{
                char* small_buffer = (char *)malloc(sizeof(char) * strlen(t.data) + 3);
                sprintf(small_buffer," %s ", t.data);
                printf("INLINE_EQ(%s)\n",t.data);
                
                break;
            }
            case BLOCK_EQ:{
                size_t spaces = 3;
                char* small_buffer = (char *)malloc(sizeof(char) * strlen(t.data) + spaces);
                sprintf(small_buffer," %s ", t.data);
                printf("BLOCK_EQ(%s)\n",t.data);
                printf("\t\t[DEBUG] doc should be: %zu\n", len_tracker);

                
                break;
            }
            case NEW_LINE:{
                char* small_buffer = (char *)malloc(sizeof(char) * strlen(t.data));
                sprintf(small_buffer,"%s", t.data);
                printf("NEW_LINE(%s)\n",t.data);
                len_tracker = len_tracker + sizeof(char) * strlen(t.data);
                printf("\t\t[DEBUG] doc should be: %zu\n", len_tracker);

                
                break;
            }
            default :{
                size_t spaces = 3;
                printf("TEXT(%s)\n",t.data);
                char* small_buffer = (char *)malloc(sizeof(char) * strlen(t.data) + spaces);
                sprintf(small_buffer,"%s ", t.data);

                break;
            }
            
        }
    }
    strcat(doc_cont,end_doc);
    printf("[DEBUG] New len doc_content buffer: %zu\n", sizeof(doc_cont));
    printf("CODE: \n%s", doc_cont);
}