#include "lexer.h"
#include "parser.h"

char *latex_content = "#{chemfig}\n"
                      "This is some very basic latex ! \\int_C x^2 dx !\n";

char *l2 = "This is a latex command block ! \\int !\n"
            "This is the second paragraph $ \\int c dx $\n";
char *l3 = "#{chemfig}\n"
            "This is a latex command block ! \\int !\n"
            "This is the second paragraph $ \\int c dx $\n";


int main() {
    printf("Hello new program\n");
    printf("Running version %s %s\n", __DATE__,__TIME__);
    token_container tokens;
    printf("Length of string: %zu\n", strlen(l3));
    printf("The string in question:\n%s\n", l3);
    lex_content(l3 ,&tokens);
    compile_tex(&tokens);
}


// int main(int argc, char* argv[]) {
//     printf("Hello new program");

// }