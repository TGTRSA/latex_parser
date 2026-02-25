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
    std::string file_content = get_file_contents(textfile);
    std::cout << "File content: " << file_content << std::endl;

    std::vector<TokenContent::paragraph> content =  lex_content(file_content);
    std::vector<TokenContent::paragraph> linked_list =  parse(content);
    TokenContent::paragraph ll = linked_list[0];
    // * This would be p1
    // Token* p_1 = &ll[0];
    // print_ll(p_1);
    //  something
    Latex latex_code;
    std::cout << "[X] Created latex struct" << std::endl;
    
    latex_code.construct_tex( linked_list);
    // int latex_code_len = latex_code.doc_content.size();
    latex_code.print();
    // }
    File file;
    file.content = latex_code.content;
    file.create(argv[1], "latex_files", ".tex");
    std::string option;
    std::cout << "Do you want to delete the file?(y/n)";
    std::cin >> option;
    if(option=="y"){
        int rc = file.rm();
        if(rc < 0){
            fprintf(stderr, "Error deleting file");
        }
    }

    return 0;
}