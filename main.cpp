// #include <chrono>
// #include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>

using paragraph = std::vector<std::string>;

std::map<int, paragraph> paragraphs;


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
};

struct Word {
    std::string content;
    int length;
    Token *next;
    int len() {
        int content_len = content.length();
        return content_len;
    }
};

struct Paragraph {
    struct Word;
};

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

void lex_content(std::string file_content) {
    int content_len = file_content.length();
    int k;
    int u;
    char paragraph_inent = '\n';
    char linespace = ' ';
    // start reading the file here
    for(int i=0;i<content_len;i++){
        char c = file_content[i];
        // identify the beginning of a command
        if(c=='!'){
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
        else if(c==linespace){
            while (u<content_len) {
                char c = file_content[u];
                if(c==linespace){
                    i = u+1;
                    break;
                }
            }
        }
        // identify NP
        else if (c==paragraph_inent) {
            
        }
    }
   
    
    std::cout << "This is the command " <<command_map[0].data << std::endl;

    
    
}

int main(int argc, char **argv) {
    std::cout << "The name of the file with " << argc << " number of chars is " << argv[1] << std::endl;
    char *textfile = argv[1];
    std::string file_content = get_file_contents(textfile);
    std::cout << "File content: " << file_content << std::endl;

    lex_content(file_content);


    return 0;
}