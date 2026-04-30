#include "parse.h"

char *latex_content = "#include {chemfig}\n"
                      "This is some very basic latex ! \\int_C x^2 dx !\n";

char *l2 = "This is a latex command block ! \\int !\n"
            "This is the second paragraph $ \\int c dx $\n";
char *l3 = "#include{chemfig}\n"
            "This is a latex command block ! \\int !\n"
            "This is the second paragraph $ \\int c dx $\n";


int main() {
    printf("Hello new program\n");
    printf("Length of string: %zu\n", strlen(l2));
    printf("The string in question:\n%s\n", l2);
    lex_content(l2);
}


// int main(int argc, char* argv[]) {
//     printf("Hello new program");

// }