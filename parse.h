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
namespace Document {
    using word = std::string;
    using sentence = std::vector<word>;
    using paragraph = std::vector<sentence>;
};

struct Token {
    std::string data;
    Grammar type;
    int end_pos;
    Token *right     = nullptr;
    Token *left      = nullptr;
    
    int len() {
        int content_len = data.length();
        return content_len;
    }
};

inline std::map<Grammar,std::string> grammar_map ={
    {BLOCK_EQ,"BLOCK_COMMAND"},
    {INLINE_EQ, "INLINE_COMMAND"},
    {WORD, "TEXT"}
};

inline bool check_if_header(std::string p_header){
    std::string include = "include";
    std::cout <<  "Comparing " << p_header << " with " << include << "\n";
    if(p_header==include){
        return true;
    }else{
        return  false;
    }
}

inline Token handle_block_eq(int c_idx, int content_len, std::string file_content) {
    std::string command_str;
    Token command;
    
    int k=c_idx+1;
    std::cout << "Inline command found at: " << c_idx << " " << file_content[c_idx] << " making k i+1 " << k << " where the symbol is " << file_content[k] << std::endl;
    while(k<content_len - 1){
        // std::cout << "Compiling latex command" << std::endl;
        char tmp_char = file_content[k+1];
        
        if(tmp_char=='!'){
            command.data+= command_str;
            command.type = BLOCK_EQ;    
            command.end_pos = k+1;
            tmp_char = ' ';
            break;
        }
        command_str+=tmp_char;
        k+=1;
        // std::cout << "The command content rn: " << command.content  << std::endl;
    }
    return command;

}

inline Token handle_inline_eq(int c_idx, int content_len, std::string file_content){
    std::string command_str;
    Token command;
    int k=c_idx+1;
    while(k<=content_len){
        char tmp_char = file_content[k+1];
        std::string tmp_string(1, tmp_char);
        if(tmp_char=='$'){
            command.data+= command_str;
            command.type = INLINE_EQ;    
            
            command.end_pos = k+1;
            tmp_char = ' ';
            break;
        }
        command_str+=tmp_string;
        k+=1;
        // std::cout << "The command content rn: " << command.content  << std::endl;
    }
    // command_map[0]= command;
    return command;
}

inline Token compile_header(int index, std::string file_content, int len_content, Token &header){
    std::cout << "Check content: " << file_content << "\n";
    std::string header_string;
    
    while(index< len_content) {
        char c = file_content[index];
        std::string c_str(1,c );
        if(c=='\n'){
            std::cout << "Found end of header at " << index << " where the char is " << c ;
            header.data = header_string;
            header.type = HEADER;
            header.end_pos = index;
            header_string = " ";
            return header;
        }
        header_string+=c_str;
        index++;
    }
    return header;
}

inline Token handle_header(int c_idx, int content_len,  std::string file_content) {
    Token header_token;
    
    std::string header;
    int u = int(c_idx+1);
    while (u<content_len) {
        char tmp_char = file_content[u];
        if(tmp_char==' '){
            tmp_char=' ';
            std::cout << "Found end of string\n";
            break;
        }
        std::string c(1, tmp_char);
        header+=c;
        std::cout << "Header: " << header << "\n";
        u++;
    }
    bool is_header = check_if_header( header);
    if(is_header){
        std::cout << "Found a header\n";
        header_token = compile_header(u, file_content, content_len, header_token);
        std::cout << "Header position in regard to struct: " <<  header_token.end_pos << std::endl;
    }else{
        std::cout << "Not a header\n";
    }



    return header_token;
}

inline Token handle_word(int c_idx, int content_len, const std::string &file_content ) {
    int u=c_idx;
    // creating memory for the word content
    std::string word = "";
    // creating word_token for the paragraph vector
    Token word_token;

    while (u<=content_len) {
        char c = file_content[u];
        word+=c;
        if(c==' '){
            word_token.data = word; 
            word_token.type = WORD;
            
            word_token.end_pos = u;
            break;
        }
        u+=1;
    }   
    return word_token;
}



#endif
