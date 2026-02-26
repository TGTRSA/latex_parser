
#ifndef FILE_HANDER_H
#define FILE_HANDER_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>

// Base struct for handling files
struct File {
    std::string content;
    std::string path;
    std::string dir;
    void create(const char* filename,std::string directory, std::string filetype) {
        this->path = directory + "/" + filename + filetype; 
        this->dir = directory;
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

    void to_pdf(){
        std::vector<std::string> cmd_base = {
            "latex -output-directory=","pdflatex "
        };
        int n_commands = cmd_base.size(); 
        for(int i=0;i<n_commands;i++){
            std::stringstream cmd;

            if(i==0){
                system("cd latex_files");
                cmd << cmd_base[i] << this->dir << " " << this->path;
            }if(i!=0){
                cmd << cmd_base[i] << this->path;
            }
            std::string cmd_string = cmd.str();
            std::cout << "Running: " << cmd_string.c_str() << "\n";
            // std::cout << "Attempting:" <<  printable;
            system(cmd_string.c_str());
        }
        // system(cmd_string.c_str());

    }

};

#endif