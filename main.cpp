// #include <chrono>
// #include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>

enum Grammar{
    COMMAND,
    WORD,
    PARAGRAPH,
};

std::map<char,Grammar> rules = {
    {'!', COMMAND}
};

struct Token {
    std::string data;
    Grammar type;
    Token *next;
    int len() {
        int content_len = data.length();
        return content_len;
    }
};

namespace DocumentContent{ 
    // the token (word, command, etc)
    using Token = ::Token;
    // paragraph being a collection of strings
    using paragraph = std::vector<Token>;
    // paragraphs being a collection of "paragraphs"
    std::map<int, paragraph> paragraphs;
}

std::map<int, Token> command_map;

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

std::vector<DocumentContent::paragraph> lex_content(std::string file_content) {
    int content_len = file_content.length();
    int k;
    int u;
    int p_idx = 0;
    char paragraph_indent = '\n';
    char linespace = ' ';
    std::vector<DocumentContent::paragraph> content_vec; 
    // start reading the file here
    for(int i=0;i<content_len;i++){
        char current_char = file_content[i];
        // identify the beginning of a command
        if(current_char=='!'){
            Token command;
            k=i+1;
            while(k<content_len && file_content[k]!='!'){
                char tmp_char = file_content[k+1];
                if(tmp_char=='!'){
                    i = k;
                    tmp_char = ' ';
                    break;

                }
                command.data+=tmp_char;
                k+=1;
                // std::cout << "The command content rn: " << command.content  << std::endl;
            }
            command_map[0]= command;
        }
        // identify the beginning of a new word
        else if(current_char!=linespace){
            u=i+1;
            // creating memory for the word content
            std::string word = "";
            // creating word_token for the paragraph vector
            DocumentContent::Token word_token;

            while (u<content_len) {
                char c = file_content[u];
                word+=c;
                if(c==linespace){
                    word_token.data = word; 
                    DocumentContent::paragraphs[p_idx].push_back(word_token);
                    i = u+1;
                    break;
                }
                u+=1;
            }
        }
        // identify NP
        else if (current_char==paragraph_indent) {
            p_idx+=1;
        }
    }
    content_vec.push_back(DocumentContent::paragraph);
    return content_vec;
}

int main(int argc, char **argv) {
    std::cout << "The name of the file with " << argc << " number of chars is " << argv[1] << std::endl;
    char *textfile = argv[1];
    std::string file_content = get_file_contents(textfile);
    std::cout << "File content: " << file_content << std::endl;

    lex_content(file_content);


    return 0;
}