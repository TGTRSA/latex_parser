#ifndef FILE_HANDER_H
#define FILE_HANDER_H

#include <filesystem>
#include <fstream>
#include <iostream>

// Base struct for handling files
struct File {
    std::string content;
    std::string path;

    void create(const char* filename,std::string directory, std::string filetype) {
        this->path = directory + "/" + filename + filetype; 
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
