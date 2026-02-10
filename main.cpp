// #include <chrono>
// #include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <fstream>

enum Grammar{
    COMMAND
};

std::map<char,Grammar> grammar_map = {
    {'!', COMMAND}
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

void read_contents(std::string file_content) {
    int content_len = file_content.length();
    int counter = 0;

    for(int i=0;i<content_len;i++){
        char c = file_content[i];
        if(c=='!'){
            counter+=1;
        }
    }

    std::cout << "There are " << counter << " bangs" << std::endl;

}

int main(int argc, char **argv) {
    std::cout << "The name of the file with " << argc << " number of chars is " << argv[1] << std::endl;
    char *textfile = argv[1];
    std::string file_content = get_file_contents(textfile);
    std::cout << "File content: " << file_content << std::endl;

    read_contents(file_content);


    return 0;
}