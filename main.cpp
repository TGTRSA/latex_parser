// #include <chrono>
// #include <cstdio>

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

// *** [TODO]:
// * []          Recognise block equation
// * []          Construct the full document
// * []          Write latex compile pipeline
// * []          Impliment writing only differences instead of while document
// //

enum Grammar{
    INLINE_COMMAND,
    BLOCK_EQ,
    WORD,
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

namespace TokenContent { 
    // the token (word, command, etc)
    using Token = ::Token;
    // paragraph being a collection of strings
    using paragraph = std::vector<Token>;
    // paragraphs being a collection of "paragraphs"
    std::map<int, paragraph> paragraphs ;
}

struct Latex {
    std::vector<std::string> doc_content;

   void construct_tex(std::vector<TokenContent::paragraph> ll){
        int len_arr = ll.size(); 

        for(int p_idx=0;p_idx<len_arr;p_idx++){
            int len_paragraph = ll[p_idx].size();
            
            for(int token_indx=0;token_indx<len_paragraph;token_indx++){
                Token& buf = ll[p_idx][token_indx];
                switch (buf.type) {
                    case WORD:
                        {
                            this->doc_content.push_back(buf.data);
                        }
                    case INLINE_COMMAND:
                        {   std::stringstream ss;
                            ss << "$ " << buf.data << " $";
                            this->doc_content.push_back(ss.str());
                        }
                    case BLOCK_EQ:
                        {
                            std::stringstream block_equation;
                            block_equation << "\\begin{equation} " << buf.data << " \\end{equation}";
                            this->doc_content.push_back(block_equation.str());
                        }    
                }
            }
        }
    }
};

std::map<int, Token> command_map;

std::vector<std::string> rules_arr;

std::map<Grammar,std::string> grammar_map ={
    {BLOCK_EQ, "BLOCK_COMMAND"},
    {INLINE_COMMAND, "INLINE_COMMAND"},
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
                    command.type = INLINE_COMMAND;    
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



    return 0;
}