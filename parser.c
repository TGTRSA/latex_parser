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
   ;
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
        switch (t.attrib) {
            case HEADER:
            {
                while(i<container->length){
                    // write header here
                    if(container->tokens[i].attrib==HEADER){
                        // change token
                        t=container->tokens[i];
                        // write_header( &t);
                        // create buffer for token data including spaces
                        char* small_buffer = (char *)malloc(sizeof(char) * strlen(t.data) + 3);
                        small_buffer[sizeof(char) * strlen(t.data) + 2] = '\0';
                        char* usepackage = "\n\\usepackage{}";
                        size_t buf_len = sizeof(char) * (strlen(small_buffer)+ strlen(usepackage));
                        char* header = (char *) malloc(buf_len + 1);
                        header[buf_len] = '\0';
                        sprintf(header," \n\\usepackage{%s} ", t.data); 
                        printf("HEADER(%s)\n",t.data);
                        printf("\t[DEBUG] HEADER: %s\n", header);
                        len_tracker = len_tracker + strlen(header);
                        printf("\t\t[DEBUG] doc should be: %zu\n", (len_tracker));
                        doc_cont = realloc(doc_cont,len_tracker);
                        printf("\t\t[DEBUG] The doc is: %zu\n", strlen(doc_cont));
                        memcpy(doc_cont + strlen(doc_cont), header,strlen(header));
                        i++;
                    }else{
                        len_tracker=len_tracker+strlen(begin_doc);
                        doc_cont = realloc(doc_cont, len_tracker);
                        memcpy(doc_cont + strlen(doc_cont),begin_doc,strlen(begin_doc));
                        break;
                    }                        
                }
                break;
            }
            case INLINE_EQ:{
                char* small_buffer = (char *)malloc(sizeof(char) * strlen(t.data) + 3);
                sprintf(small_buffer," %s ", t.data);
                printf("INLINE_EQ(%s)\n",t.data);
                len_tracker = len_tracker + sizeof(char) * strlen(small_buffer);
                printf("\t\t[DEBUG] doc should be: %zu\n", len_tracker);
                break;
            }
            case BLOCK_EQ:{
                size_t spaces = 3;
                char* small_buffer = (char *)malloc(sizeof(char) * strlen(t.data) + spaces);
                sprintf(small_buffer," %s ", t.data);
                printf("BLOCK_EQ(%s)\n",t.data);
                len_tracker = len_tracker + sizeof(char) * strlen(small_buffer);
                printf("\t\t[DEBUG] doc should be: %zu\n", len_tracker);
                break;
            }
            case NEW_LINE:{
                char* small_buffer = (char *)malloc(sizeof(char) * strlen(t.data));
                sprintf(small_buffer,"%s", t.data);
                printf("NEW_LINE(%s)\n",t.data);
                len_tracker = len_tracker + sizeof(char) * strlen(small_buffer);
                printf("\t\t[DEBUG] doc should be: %zu\n", len_tracker);

                
                break;
            }
            default :{
                size_t spaces = 3;
                printf("TEXT(%s)\n",t.data);
                char* small_buffer = (char *)malloc(sizeof(char) * strlen(t.data) + spaces);
                len_tracker = len_tracker + strlen(small_buffer);
                printf("\t\t[DEBUG] doc should be: %zu\n", len_tracker);
                sprintf(small_buffer,"%s ", t.data);
                break;
            }
            
        }
    }
    strcat(doc_cont,end_doc);
    printf("[DEBUG] New len doc_content buffer: %zu\n", sizeof(doc_cont));
    printf("CODE: \n%s", doc_cont);
}