// #include <chrono>
// #include <cstdio>
#include <iostream>
#include <string>
#include <fstream>


std::string read_file(char *textfile) {
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


int main(int argc, char **argv) {
    // printf("Starting program\n");
    // printf("The name of the file is %s with %d number of chars", argv[1], argc);
    std::cout << "The name of the file with " << argc << " number of chars is " << argv[1] << std::endl;
    char *textfile = argv[1];
    std::string file_content = read_file(textfile);
    std::cout << "File content: " << file_content << std::endl;
    return 0;
}