#ifndef PARSER_H
#define PARSER_H

#include <filesystem>
#include <fstream>
#include <iostream>

struct File {
    std::string content;
    std::string path;

    void create(const char* filename,std::string dirname) {
        this->path = dirname + "/" + filename; 
        std::cout << "Attempting to create: " << path << std::endl;        
        std::ofstream file(this->path);
        file << content;
        file.close();
    };

    int rm(){
        try{std::filesystem::remove(this->path);
            printf("File deleted\n");
            return 0;
        }catch (const std::filesystem::filesystem_error& e) {
            printf("Error: %s\n", e.what());
            return -1;
        }
        
    }

};

#endif
