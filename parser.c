#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* latex_code = "\\documentclass{article}\n"
                    "\\usepackage[utf8]{inputenc}\n"
                    "\\usepackage{asmath}\n"
                    "\\usepackage{tikz}\n"
                    "\\usepackage{geometry}";

const char* begin_doc  = "\n\\begin{document}\n";
const char* end_doc    = "\\end{document}\n";
bool header_written=false;

void write_header(Token *t) {
    printf("%s\n", t->data);
    
    char* usepackage = "\\usepackage{}";
    char* buf = (char *)  malloc(  sizeof(char) * strlen(latex_code));
    size_t doc_opening_len = sizeof(char) * strlen(usepackage) + strlen(t->data) + strlen(latex_code);
    char* full_tex = (char *) (malloc(doc_opening_len )); 
    char* buffer = (char *) malloc(sizeof(char)*(strlen(usepackage)+strlen(t->data)));
    
    // taking the latex content and putting it into a buffer that can handle it 
    // then creating the psckage and appending it to the buffer
    strcpy(full_tex,latex_code);
    // free(latex_code);
    sprintf(buffer,  "\n\\usepackage{%s}", t->data);
    strcat(full_tex,buffer);

    latex_code = (char *) malloc(sizeof(char) * strlen(full_tex) + 1);

    free(buffer);
    latex_code = full_tex;
    printf("%s\n", latex_code);

    // free(full_tex);
}

void compile_tex(token_container *container){
    printf("\n[DEBUG] In parser.h:\n");
    size_t i;    
    for(i=0;i<container->length;i++){
        Token t = container->tokens[i] ;
        switch (t.attrib) {
            case HEADER:
            {
                printf("HEADER(%s)\n",t.data);
                write_header( &t);
                printf("%s\n",latex_code);
                break;
            }
            case INLINE_EQ:{
                printf("INLINE_EQ(%s)\n",t.data);
                break;
            }
            case BLOCK_EQ:{
                printf("BLOCK_EQ(%s)\n",t.data);
                break;
            }
            case NEW_LINE:{
                printf("NEW_LINE(%s)\n",t.data);
                break;
            }
            default :{
                printf("TEXT(%s)\n",t.data);
                break;
            }
            
        }
    }

}