#ifndef PARSER_H
#define PARSER_H
#include "useful_funcs.h"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "file_handler.h"

// Describes the patterns of tokens well see
enum Grammar{
    INLINE_EQ,
    BLOCK_EQ,
    WORD,
    HEADER,
};

// Describes the information for each item of the document \f
struct Token {
    std::string data;
    Grammar     type;
    int         end_pos;
    Token       *right     = nullptr;
    Token       *left      = nullptr;
    
    int len() const {
        int content_len = data.length();
        return content_len;
    }
};

// Describes the document structure and uses new names for ease of use
namespace Document {
    using identifier = Token;                   // single token: word, command etc
    using sentence   = std::vector<identifier>; // collection of tokens therefore sentence
    using paragraph  = std::vector<sentence>;   // collection of setences
    using full_      = std::vector<paragraph>;  // complete document of paragraphs
};

inline std::map<Grammar,std::string> grammar_map ={
    {BLOCK_EQ,"BLOCK_COMMAND"},
    {INLINE_EQ, "INLINE_COMMAND"},
    {WORD, "TEXT"}
};

// checks if content followed by # is a header file
inline bool check_if_header(const std::string& p_header){
    const std::string include = "include";
    std::cout <<  "Comparing " << p_header << " with " << include << "\n";
    return p_header == include;
}

inline Token compile_block_equation(size_t& block_pos, const std::string& contents, const int& len_content){
    Document::identifier t;
    return t;
}

inline Token compile_inline_command(size_t& inline_pos, const std::string& contents, const int& len_content){
    Document::identifier t;
    return t;
}

inline Token compile_word(size_t& word_pos, const std::string& contents, const int& len_content){
    Document::identifier t;
    return t;
}

inline Token compile_header(size_t& header_pos, const std::string& contents, int len_content){
    size_t h_p = header_pos+1;
    std::string tmp_string;
    Document::identifier t;
    while(h_p<len_content){
        char c = contents[h_p];
        if(c==' '){
            break;
        }
        tmp_string+=c;
        h_p++;
    }
    bool b_header =  check_if_header(tmp_string);
    if(!b_header){        
        // not a header so delegate to compile word
        header_pos-=1;
        t = compile_word(header_pos,contents, len_content);
        return t;
    }else{
        // ? at this point header_pos is at a space ' ' which will be followed by {} which means i should skip +2 because '#{chemfig}       
        header_pos+=2;
        while(header_pos<len_content){
            char c = contents[header_pos];
            if(c=='}'){
                t.type = HEADER;
                t.end_pos = header_pos;
                break;
            }
            t.data+=c;
            header_pos++;
        }
    }
    return t;
}

inline Document::full_ lex_content(const std::string& file_content){
    int len_content = file_content.size();
    int p_indx = 0;

    Document::full_ full_;
    Document::paragraph p;
    Document::sentence s;

    for(size_t i = 0; i<len_content;i++){
        char c = file_content[i];
        switch (c) {
            case '#':
            {
                Token header = compile_header(i, file_content, len_content);
                s.push_back(header);
                break;
            }
            case '!':
            {
                Token block = compile_block_equation(i, file_content, len_content);
                s.push_back(block);
                break;
            }
            case '$':
            {
                Token inline_c = compile_inline_command(i, file_content, len_content);
                s.push_back(inline_c);
                break;
            }
            case '\n':
            {
                p.push_back(s);
                s.clear();
                break;
            }
            default:
            {
                Token t = compile_word(i, file_content, len_content);
                break;
            }
        }
    }
    full_.push_back(p);
    return full_;
}

#endif
