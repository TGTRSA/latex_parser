// #include <chrono>
// #include <cstdio>
#include "useful_funcs.h"
#include <iostream>
#include <string>
#include <vector>
#include "file_handler.h"
#include "parse.h"

// *** [TODO]:
// * [X]          Recognise block equation
// * [X]          Write equation block
// * [X]          Write inline
// * [X]          Add support for more libs - chemfig etc ...
// * [X]          Construct the full document
// * []           Take into account the end of paragraphs so you can add "\n"
// * []          Write latex compile pipeline
// * []          Impliment writing only differences instead of while document

int main(int argc, char **argv) {
    std::cout << "The name of the file with " << argc << " number of chars is " << argv[1] << std::endl;
    char *textfile = argv[1];
    InputFile latex_input;
    latex_input.get_file_contents(textfile);
    std::cout << "File content: \n" << latex_input.content << std::endl;

    // std::vector<TokenContent::paragraph> content =  lex_content(file_content);
    // std::vector<TokenContent::paragraph> linked_list =  parse(content);
    // TokenContent::paragraph ll = linked_list[0];
   

    return 0;
}