// #include <chrono>
// #include <cstdio>
#include "useful_funcs.h"
#include <iostream>
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

    Document::full_ content =  lex_content(latex_input.content);
    // Parser p;
    // p.doc_content =content;
    // content = link(content);
    // p.compile_latex();
    // p.print_();
    Document::full_ doc_ = content;
    Document::paragraph par = doc_[0];
    int par_len = par.size();
    //printing the parsed tokens
    for(int i = 0;i<par_len;i++)
    {
        Document::sentence s  = par[i];
        int len_s = s.size();
        for(int j = 0; j<len_s ;j++)
        {
            Token& t =  s[j];
            std::cout << "Token: " << t.data << "\n";
        }
    } 
    

    // size_t n_tokens = content[0].size();
    // for(size_t i=0;i<n_tokens;i++){
    //     std::cout << "Number of tokens: " << n_tokens << "\n";
    //     std::cout << content[0][i][i].data << std::endl;
    // }
    // std::cout << content[0][0][1].data << " " << content[0][1][0].data << std::endl;
    // std::vector<TokenContent::paragraph> linked_list =  parse(content);
    // TokenContent::paragraph ll = linked_list[0];
   

    return 0;
}