#ifndef PARSER_H
#define PARSER_H

#include <filesystem>
#include <fstream>
#include <iostream>

struct File {
    std::string content;
    int success = 0;
    std::string path;

    void create(const char* filename,std::string dirname) {
        this->path = dirname + "/" + filename; 
        std::cout << "Attempting to create: " << path << std::endl;        
        std::ofstream file(this->path);
        file << content;
        file.close();
    };

    void rm(){
        try{std::filesystem::remove(this->path);
        printf("File deleted\n");
        }catch (const std::filesystem::f) {
            printf("Error: %s\n", e.what());
        }
    }

};

#endif
