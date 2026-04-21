// #include <chrono>
// #include <cstdio>
#include "useful_funcs.h"
#include <iostream>
#include "file_handler.h"
#include "parse.h"
#include "string_lib.h"
// *** [TODO]:
// * [X]          Recognise block equation
// * [X]          Write equation block
// * [X]          Write inline
// * [X]          Add support for more libs - chemfig etc ...
// * [X]          Construct the full document
// * [X]           Take into account the end of paragraphs so you can add "\n"
// * []          Write latex compile pipeline
// * []          Impliment writing only differences instead of while document

std::string latex_string = R"(
#include{chemfig}
This is a latex command block ! \int !

This is the second paragraph $ \int c dx $
)";

std::string latex_string2 = R"(
#include {chemfig}

This is a latex command block ! \int x^2 !

This is the second paragraph $ \int c dx $
)";

int main() {
    //std::cout << "The name of the file with " << argc << " number of chars is " << argv[1] << std::endl;
    //char *textfile = argv[1];
   // InputFile latex_input;
 //   latex_input.get_file_contents(latex_string);
    //std::cout << "File content: \n" << latex_input.content << std::endl;

    Document::full_ content =  lex_content(latex_string);
    Parser p;
    p.doc_content =content;
    // content = link(content);
    std::string latex_code =  p.compile_latex();
    p.print_();

    //File f;

    //if(endsin(argv[1],".txt" )){
      //  std::string t = replace(argv[1], ".txt", "");
        //std::cout << t << "\n";
    //}
    // f.create(textfile, "latex_files");

    // Document::full_ doc_ = content;
    // Document::paragraph par = doc_[0];
    // int par_len = par.size();
    // //printing the parsed tokens
    // for(int i = 0;i<par_len;i++)
    // {
    //     Document::sentence s  = par[i];
    //     int len_s = s.size();
    //     for(int j = 0; j<len_s ;j++)
    //     {
    //         Token& t =  s[j];
    //         std::cout << "Token: " << t.data << "\n";
    //     }
    // }

    return 0;
}
