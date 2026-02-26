#ifndef PARSER_H
#define PARSER_H
// #include <chrono>
// #include <cstdio>
// #include <chrono>
// #include <cstdio>
#include "useful_funcs.h"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "file_handler.h"


enum Grammar{
    INLINE_EQ,
    BLOCK_EQ,
    WORD,
    HEADER,
};
//  for final document => arr[i] =  paragraph => arr[i][j] = word


struct Token {
    std::string data;
    Grammar type;
    int end_pos;
    Token *right     = nullptr;
    Token *left      = nullptr;
    
    int len() const {
        int content_len = data.length();
        return content_len;
    }
};



namespace Document {
    using identifier = Token;
    using sentence   = std::vector<identifier>;
    using paragraph  = std::vector<sentence>;
};

inline std::map<Grammar,std::string> grammar_map ={
    {BLOCK_EQ,"BLOCK_COMMAND"},
    {INLINE_EQ, "INLINE_COMMAND"},
    {WORD, "TEXT"}
};

inline bool check_if_header(const std::string& p_header){
    std::string include = "include";
    std::cout <<  "Comparing " << p_header << " with " << include << "\n";
    return p_header == include;
}

inline void compile_block_equation(size_t& block_pos){

}

inline void compile_inline_command(size_t& inline_pos){

}

inline void compile_header(size_t& header_pos){

}

inline void compile_word(size_t& word_pos){

}

inline void lex_content(const std::string& file_content){
    int len_content = file_content.size();
    
    for(size_t i = 0; i<len_content;i++){
        char c = file_content[i];
        switch (c) {
            case '#':
            {
                compile_header(i);
                break;
            }
            case '!':
            {
                compile_block_equation(i);
                break;
            }
            case '$':
            {
                compile_inline_command(i);
                break;
            }
            case '\n':
            {
                ;
                break;
            }
            default:
            {
                compile_word(i);
                break;
            }
        }
    }

}

#endif
