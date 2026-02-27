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
    std::string     data;
    Grammar         type;
    size_t          end_pos;
    size_t          start_pos;
    Token           *right     = nullptr;
    Token           *left      = nullptr;
    
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
    {WORD, "TEXT"},
    {HEADER, "HEADER"}
};

class Parser {
    public:
        Document::full_ all_content;


};

// checks if content followed by # is a header file
inline bool check_if_header(const std::string& p_header){
    const std::string include = "include";
    std::cout <<  "Comparing " << p_header << " with " << include << "\n";
    return p_header == include;
}

inline Token compile_block_equation(size_t& c_pos, const std::string& contents, size_t len_content){
    Document::identifier t;
    c_pos++;
    while(c_pos<len_content){
        char c = contents[c_pos];
        if(c=='!'){
            t.type = BLOCK_EQ;
            t.end_pos=c_pos;
            break;
        }
        t.data+=c;
        c_pos++;
    }

    return t;
}

inline Token compile_inline_command(size_t& inline_pos, const std::string& contents, size_t len_content){
    Document::identifier t;
    size_t len_con = contents.size();
    t.start_pos = inline_pos; 
    inline_pos++;
    while(inline_pos<len_con){
        char c = contents[inline_pos];
        if(c == '!'){
            t.end_pos   = inline_pos;
            t.type      = INLINE_EQ;
        }
        t.data+=c;
        inline_pos++;
    }
    return t;
}

inline Token compile_word(size_t& word_pos, const std::string& contents, size_t len_content){
    Document::identifier t;
    while(word_pos < len_content){
        char c = contents[word_pos];
        if(c == ' '){
            // index at space
            t.end_pos = word_pos;
            t.type = WORD;
            break;
        }
        t.data+=c;
        word_pos++;
    }
    return t;
}

inline Token compile_header(size_t& header_pos, const std::string& contents, size_t len_content){
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
        h_p+=2;
        while(h_p<len_content){
            char c = contents[h_p];
            if(c=='}'){
                t.type = HEADER;
                t.end_pos = h_p;
                break;
            }
            t.data+=c;
            h_p++;
        }
    }
    return t;
}
// takes in the content as string and spits out a vector of vectors meant to act as a container for 'pargraphs of text'
inline Document::full_ lex_content(const std::string& file_content){
    size_t len_content = file_content.size();

    Document::full_ full_;
    Document::paragraph p;
    Document::sentence s;

    for(size_t i = 0; i<len_content;i++){
        char c = file_content[i];
        if(c!=' '){
            std::cout << "Current position: " << i << " and char at pos: " << c << "\n";
        }
        switch (c) {
            case '#':
            {
                Token header = compile_header(i, file_content, len_content);
                std::cout << "Created header token now appending...\n"; 
                s.push_back(header);
                i = header.end_pos;
                break;
            }
            case '!':
            {
                Token block = compile_block_equation(i, file_content, len_content);
                std::cout << "Created block equation token now appending...\n";  
                s.push_back(block);
                i = block.end_pos;
                break;
            }
            case '$':
            {
                Token inline_c = compile_inline_command(i, file_content, len_content);
                s.push_back(inline_c);
                i=inline_c.end_pos;
                break;
            }
            case '\n':
            {
                p.push_back(s);
                std::cout << "Found new paragraph\n";
                s.clear();
                break;
            }
            default:
            {
                Token t = compile_word(i, file_content, len_content);
                s.push_back(t);
                std::cout << "Created word token now appending...\n"; 
                i = t.end_pos;
                break;
            }
        }
    }
    full_.push_back(p);
    for(int i = 0 ; i<full_.size();i++){
        int paragraphs = full_[0].size();
        Document::paragraph p = full_[i];
        for(int j = 0;j<paragraphs;j++){
            Document::sentence sen = p[j];
            int sen_len = sen.size();
            for(int k=0;k<sen_len;k++){
                std::stringstream ss; ss  << grammar_map[sen[k].type] << "(" << sen[k].data << ")\n"; 
                std::cout << ss.str() <<std::endl ;
            }
        }
    }
    return full_;
}

#endif
