#include "parser.h"

void compile_tex(token_container *container){
    printf("[DEBUG] \nIn parser.h:\n");
    size_t i;    
    for(i=0;i<container->length;i++){
        Token t = container->tokens[i] ;
        switch (t.attrib) {
            case HEADER:
            {
                printf("HEADER(%s)\n",t.data);
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