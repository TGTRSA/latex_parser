
#ifndef FILE_HANDER_H
#define FILE_HANDER_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>

// struct for handling the latex file
struct InputFile {
    std::string content;        // the physical content it will contain

    
    void get_file_contents(char *filename) {
        std::string tmp_string;
        std::string file_contents;
        std::ifstream file(filename);
        char ch;
        printf("This is the contents of the text file:\n%s", file_contents.c_str());
        if(file.is_open()){
            while (file.get(ch)) {
                this->content+=ch;
            }       
        }else {
            std::cerr << "Failed to open file" << std::endl;
        }
    }
};

// Base struct for handling files
struct File {
    std::string content;    // actual content
    std::string path;       // full path
    std::string dir;        // solely used for directory
    
    // well ... im sure u can tell
    void create(const char* filename,std::string directory, std::string filetype) {
        this->path = directory + "/" + filename + filetype; 
        this->dir = directory;
        std::cout << "Attempting to create: " << path << std::endl;        
        std::ofstream file(this->path);
        file << content;
        file.close();
    };

    // removes the file
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