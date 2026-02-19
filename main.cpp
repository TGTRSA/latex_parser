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
// * [X]          Recognise block equation
// * [X]          Write equation block
// * [X]          Write inline
// * [X]          Add support for more libs - chemfig etc ...
// * [X]          Construct the full document
// * []          Write latex compile pipeline
// * []          Impliment writing only differences instead of while document

enum Grammar{
    INLINE_EQ,
    BLOCK_EQ,
    WORD,
    HEADER,
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
    // ? This might be a naming issue in that the Token has the paragraph no??? 
    using paragraph = std::vector<Token>;
    // paragraphs being a collection of "paragraphs"
    // ! Is this even being used??
    std::vector<paragraph> paragraphs ;
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
                // std::cout << "[X] Got token from fake linked list" <<std::endl;
                // std::cout << "Attempting to append to doc_content" << std::endl;
                if (buf.type==HEADER)
                {
                    std::cout << buf.data << " is a header" << std::endl;
                    std::stringstream header;
                    header << "\\usepackage{" << buf.data << "}" << std::endl; 
                    std::string header_string = header.str();
                    this->paragraph.push_back(header_string);
                }
                else if(buf.type==WORD)
                {                       
                    std::cout << buf.data << " is a string" << std::endl; 
                    this->paragraph.push_back(buf.data);
                }
                else if(buf.type == INLINE_EQ)
                {   
                    std::cout << buf.data << " is an inline command" << std::endl;
                    std::stringstream inline_equation;
                    inline_equation << "$ " << buf.data << " $";
                    
                    std::string inline_equation_string = inline_equation.str();
                    std::cout << inline_equation_string <<std::endl ;
                    this->paragraph.push_back(inline_equation_string);
                    
                }
                else if(buf.type == BLOCK_EQ) 
                {
                    std::cout << buf.data << " is a block equation" << std::endl;
                    std::stringstream block_equation;
                    block_equation << "\\begin{equation} " << buf.data << " \\end{equation}";
                    
                    std::string block_eq_string = block_equation.str();
                    std::cout << block_eq_string << std::endl;
                    this->paragraph.push_back(block_eq_string);
                    
                }
                }
            }
            this->paragraphs_sequence.push_back(this->paragraph);
            
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

// std::map<const char, Grammar> symbols_lookup_table = {
//     {'!', BLOCK_EQ},
//     {'$', INLINE_EQ},
//     {'#', HEADER}
// };

std::map<Grammar,std::string> grammar_map ={
    {BLOCK_EQ,"BLOCK_COMMAND"},
    {INLINE_EQ, "INLINE_COMMAND"},
    {WORD, "TEXT"}
};

std::string get_file_contents(char *textfile) {
    std::string tmp_string;
    std::string file_contents;
    std::ifstream file(textfile);
    char ch;
    
    if(file.is_open()){
        while (file.get(ch)) {
            // printf("This is the contents of the text file:\n%s", file_contents.c_str());
            std::cout << ch << std::endl;
            file_contents += ch;    
        }       
    }else {
        std::cerr << "Failed to open file" << std::endl;
    }

    return file_contents;
}

bool check_if_header(std::string p_header){
    std::string include = "include";
    std::cout <<  "Comparing " << p_header << " with " << include << "\n";
    if(p_header==include){
        return true;
    }else{
        return  false;
    }
}

int handle_block_eq(int c_idx, int p_idx, int content_len, const std::string  &file_content) {
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
            TokenContent::paragraphs[p_idx].push_back(command);
            c_idx = k + 1;
            tmp_char = ' ';
            break;
        }
        command_str+=tmp_char;
        k+=1;
        // std::cout << "The command content rn: " << command.content  << std::endl;
    }
    return c_idx;

}

int handle_inline_eq(int c_idx, int p_idx, int content_len, const std::string &file_content){
    std::string command_str;
    Token command;
    int k=c_idx+1;
    while(k<content_len && file_content[k]!='!'){
        char tmp_char = file_content[k+1];
    
        if(tmp_char=='$'){
            command.data+= command_str;
            command.type = INLINE_EQ;    
            TokenContent::paragraphs[p_idx].push_back(command);
            c_idx = k;
            tmp_char = ' ';
            break;
        }
        command_str+=tmp_char;
        k+=1;
        // std::cout << "The command content rn: " << command.content  << std::endl;
    }
    // command_map[0]= command;
    return c_idx;
}

int handle_header(int c_idx, int p_idx, int content_len, const std::string &file_content) {
    std::cout << "Found header str??\n"; 
    int c = c_idx+1; 
    std::string tmp_str;
    std::cout << "c is " <<  c << " at #\n";
    while(file_content[c]!=' '){
        tmp_str+=file_content[c];
        c++;
    }
    bool is_header = check_if_header(tmp_str);
    if(is_header){
        Token header_token;
        std::string header_name;
        int h = c +1;
        std::cout << " now c is " << c <<  std::endl;
        while (h<content_len) {
            char tmp_c = file_content[h];
            if(tmp_c=='\n'){
                header_token.data = header_name;
                header_token.type = HEADER;
                TokenContent::paragraphs[p_idx].push_back(header_token);
                c_idx=h;
                tmp_c = ' ';
                break;
            }
            header_name+=tmp_c;
            h+=1;
        }
    }
    return c_idx;
}

int handle_word(int c_idx,int p_idx, int content_len, const std::string &file_content ) {
    int u=c_idx;
    // creating memory for the word content
    std::string word = "";
    // creating word_token for the paragraph vector
    TokenContent::Token word_token;

    while (u<content_len) {
        char c = file_content[u];
        word+=c;
        if(c==' '){
            word_token.data = word; 
            word_token.type = WORD;
            TokenContent::paragraphs[p_idx].push_back(word_token);
            c_idx = u;
            break;
        }
        u+=1;
    }   
    return c_idx;
}

std::vector<TokenContent::paragraph> lex_content(const std::string &file_content) {
    std::vector<TokenContent::paragraph> paragraphs;
    paragraphs.emplace_back(); // start first paragraph
    int content_len = file_content.length();
    int u;
    int p_idx = 0;
    int new_pos;
    // char paragraph_indent = '\n';
    char linespace = ' ';
    char inline_command_start = '$';
    // char block_command_start = '!';
    std::string header_begin = "use_p";

    std::vector<TokenContent::paragraph> content_vec; 
    // start reading the file here
    for(int i=0;i<content_len;i++){
        char current_char = file_content[i];
        std::cout << "Current char: " << current_char << std::endl;
        // identify the beginning of a command
        
        for (int i = 0; i < content_len; ++i) {
            char c = file_content[i];

            switch (c) {
                case '!':
                    i = handle_block_eq(i, p_idx, content_len, file_content);
                    break;

                case '$':
                    i = handle_inline_eq(i, p_idx, content_len, file_content);
                    break;

                case '#':
                    i = handle_header(i, p_idx, content_len, file_content);
                    break;

                case '\n':
                    ++p_idx;
                    break;

                case ' ':
                    break;  // ignore spaces

                default:
                    i = handle_word(i, p_idx, content_len, file_content);
                    break;
                }   
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

void print_ll(Token* head){
    if (typeid(head)!=typeid(nullptr)){
        // std::cout << head->data << " ";
        Token *n_head = head->right;
        print_ll(n_head);
    }

}

int main(int argc, char **argv) {
    // int p= 0;
    // while(p<10){
    //     if(argv[p]){

    //     }else{
    //         break;
    //     }
    //     p+=1;
    // }
    // for(int o=1;o<p;o++){
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
    

    return 0;
}