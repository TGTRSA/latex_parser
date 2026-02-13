// #include <chrono>
// #include <cstdio>
#include "useful_funcs.h"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

// *** [TODO]:
// * []          Recognise block equation
// * []          Write equation block
// * []          Write inline
// * []          Add support for more libs - chemfig etc ...
// * []          Construct the full document
// * []          Write latex compile pipeline
// * []          Impliment writing only differences instead of while document

enum Grammar{
    INLINE_EQ,
    BLOCK_EQ,
    WORD,
};

//  for final document => arr[i] =  paragraph => arr[i][j] = word
namespace Document {
    using paragraphs = std::vector<std::vector<std::string>>;
    using paragraph  = std::vector<std::string>; 
};


struct Token {
    Token *right     = nullptr;
    Token *left      = nullptr;
    std::string data;
    Grammar type;
   
    int len() {
        int content_len = data.length();
        return content_len;
    }
};

// for lexing and parsing
namespace TokenContent { 
    // the token (word, command, etc)
    using Token = ::Token;
    // paragraph being a collection of strings
    using paragraph = std::vector<Token>;
    // paragraphs being a collection of "paragraphs"
    std::map<int, paragraph> paragraphs ;
}

struct Latex {
    Document::paragraphs paragraphs_sequence;
    Document::paragraph paragraph;

    //  takes the linked list and turns the code inside of into the latex_code and appends to string vector 
    void construct_tex(std::vector<TokenContent::paragraph> token_linked_list){
        int len_arr = token_linked_list.size(); 
        
        for(int p_indx=0;p_indx<len_arr;p_indx++){
            int len_paragraph = token_linked_list[p_indx].size();
            std::cout << "Length of paragraph: " << len_paragraph << std::endl;
            for(int token_indx=0;token_indx<len_paragraph;token_indx++){
                Token& buf = token_linked_list[p_indx][token_indx];
                std::cout << "[X] Got token from fake linked list" <<std::endl;
                // ![FIX]: BUG with allocation issue
                switch (buf.type) {
                    case WORD:
                        {                       
                            std::cout << "Attempting to append to doc_content" << std::endl; 
                            this->paragraph.push_back(buf.data);
                            break;
                        }
                    case INLINE_EQ:
                        {   
                            std::stringstream inline_equation;
                            inline_equation << "$ " << buf.data << " $";
                            std::string inline_equation_string = inline_equation.str();
                            this->paragraph.push_back(inline_equation_string);
                            break;
                        }
                    case BLOCK_EQ:
                        {
                            std::stringstream block_equation;
                            block_equation << "\\begin{equation} " << buf.data << " \\end{equation}";
                            
                            this->paragraph.push_back(block_equation.str());
                            break;
                        }
                }
            }
            this->paragraphs_sequence.push_back(this->paragraph);
            
        }
    }


    void print() {
        std::cout << "Starting print sequence " << std::endl;
        int latex_code_len = this->paragraphs_sequence.size();
        for(int p_indx = 0;p_indx<latex_code_len;p_indx++){
            int len_paragraph = this->paragraphs_sequence[p_indx].size();

            for(int word_indx=0;word_indx<len_paragraph;word_indx++){
                std::string str_buf = this->paragraphs_sequence[p_indx][word_indx];
                std::cout << str_buf;
                
            }
            print_nl();
        }
    }

};

std::map<int, Token> command_map;

std::vector<std::string> rules_arr;

std::map<const char, Grammar> symbols_lookup_table = {
    {'!',BLOCK_EQ},
    {'$', INLINE_EQ}
};

std::map<Grammar,std::string> grammar_map ={
    {BLOCK_EQ,"BLOCK_COMMAND"},
    {INLINE_EQ, "INLINE_COMMAND"},
    {WORD, "TEXT"}
};

std::string get_file_contents(char *textfile) {
    std::string tmp_string;
    std::string file_contents;
    std::fstream stream;
    stream.open(textfile);
    if(stream.is_open()){
        while (std::getline(stream,tmp_string)) {
            // printf("This is the contents of the text file:\n%s", file_contents.c_str());
            std::cout << tmp_string << std::endl;
            file_contents += tmp_string;    
        }
        
    }else {
        std::cerr << "Failed to open file" << std::endl;
    }

    return file_contents;
}

std::vector<TokenContent::paragraph> lex_content(std::string file_content) {
    int content_len = file_content.length();
    int k;
    int u;
    int p_idx = 0;
    char paragraph_indent = '\n';
    char linespace = ' ';
    char inline_command_start = '$';
    char block_command_start = '!';

    std::vector<TokenContent::paragraph> content_vec; 
    // start reading the file here
    for(int i=0;i<content_len;i++){
        char current_char = file_content[i];
        std::cout << "Current char: " << current_char << std::endl;
        // identify the beginning of a command
        if(current_char==inline_command_start){
            std::string command_str;
            Token command;
            k=i+1;
            while(k<content_len && file_content[k]!=inline_command_start){
                char tmp_char = file_content[k+1];
                
                if(tmp_char==inline_command_start){
                    command.data+= command_str;
                    command.type = INLINE_EQ;    
                    TokenContent::paragraphs[p_idx].push_back(command);
                    i = k;
                    tmp_char = ' ';
                    break;
                }
                command_str+=tmp_char;
                k+=1;
                // std::cout << "The command content rn: " << command.content  << std::endl;
            }
            // command_map[0]= command;
        }
        // identify the beginning of a new word
        else if(current_char!=linespace && current_char!=inline_command_start){
            u=i;
            // creating memory for the word content
            std::string word = "";
            // creating word_token for the paragraph vector
            TokenContent::Token word_token;

            while (u<content_len) {
                char c = file_content[u];
                word+=c;
                if(c==linespace){
                    word_token.data = word; 
                    word_token.type = WORD;
                    TokenContent::paragraphs[p_idx].push_back(word_token);
                    i = u;
                    break;
                }
                u+=1;
            }
        }else if (current_char==block_command_start) {
            std::string command_str;
            Token command;
            k=i+1;
            while(k<content_len && file_content[k]!=block_command_start){
                char tmp_char = file_content[k+1];
                
                if(tmp_char==inline_command_start){
                    command.data+= command_str;
                    command.type = BLOCK_EQ;    
                    TokenContent::paragraphs[p_idx].push_back(command);
                    i = k;
                    tmp_char = ' ';
                    break;
                }
                command_str+=tmp_char;
                k+=1;
                // std::cout << "The command content rn: " << command.content  << std::endl;
            }
            // command_map[0]= command;
        }
        // identify NP
        else if (current_char==paragraph_indent) {
            p_idx+=1;
        }
    }
    int n = TokenContent::paragraphs.size();
    for(int i=0;i<n;i++){
        content_vec.push_back(TokenContent::paragraphs[i]);
    }
    return content_vec;
}

std::vector<TokenContent::paragraph> parse(std::vector<TokenContent::paragraph> lexed_content){
    int n = lexed_content.size();
    std::cout << "Number of paragraphs: " << n << std::endl; 
    // int p_indx=0;
    for(int p_indx =0;p_indx<n;p_indx++){
        int len_paragraph = lexed_content[p_indx].size();
        std::cout << "Length of paragraph: " << len_paragraph << std::endl;
        
        for(int token_indx=0;token_indx<len_paragraph; token_indx++){
            
            std::cout <<" Current token: " << lexed_content[p_indx][token_indx].data << std::endl;

            if(lexed_content[p_indx][token_indx].left==nullptr){
                // set a left Token
                if((token_indx-1)!=-1){                    
                    lexed_content[p_indx][token_indx].left = &lexed_content[p_indx][token_indx-1];    
                }

            }if(lexed_content[p_indx][token_indx].right==nullptr){
                // set right token
                if((token_indx)!=len_paragraph-1){
                    
                    lexed_content[p_indx][token_indx].right =&lexed_content[p_indx][token_indx+1];
                } 
            }
        }
    }
    // std::cout << "lexed_content[0][1].right->data: " << lexed_content[0][0].right->data << std::endl;
    // ? Maybe research the methods used for storing tokens even tho the linked list seems efficient
    // ! Important : This is a linked list not just lexed content so treat it that way
    return lexed_content;    
}

int main(int argc, char **argv) {
    std::cout << "The name of the file with " << argc << " number of chars is " << argv[1] << std::endl;
    char *textfile = argv[1];
    std::string file_content = get_file_contents(textfile);
    std::cout << "File content: " << file_content << std::endl;

    std::vector<TokenContent::paragraph> content =  lex_content(file_content);
    std::vector<TokenContent::paragraph> linked_list =  parse(content);
    
    Latex latex_code;
    std::cout << "[X] Created latex struct" << std::endl;
    latex_code.construct_tex( linked_list);
    // int latex_code_len = latex_code.doc_content.size();
    latex_code.print();

    return 0;
}