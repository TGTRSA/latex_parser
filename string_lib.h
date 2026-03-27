#ifndef STRINGY
#define STRINGY

inline int strlen(const char* str){
    int strlen= 0;
    while(str[strlen] !='\0'){
        strlen++;
    }
    return strlen;
}

inline bool endsin(const char* string, const char* end) {
    int len_ = strlen(string);
    bool same = true;
    // int u=0;
    for(int i=0; i<len_;i++){
        if(end[0]==string[i]){
            ;
        }else{
            same=false;
        }
    }   
    
    return same;
}

inline char* replace(char*& original_string,const char* str1,const char* str2) {
    int lenstring = strlen(str1);
    int u = 0;
    for(int i = 0 ; i <lenstring ; i++ ){
        if(str1[0]==original_string[i] and original_string[i] != ' '){
            while(original_string[i]==str1[u]){
                original_string[i] = str2[u];
                i++;
                u++;
            }
        }
    }
    return original_string;
}

#endif