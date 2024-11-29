#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <stdlib.h> 

int main(int argc , char* argv[] ){
    std::string name;
    std::string string_temp;
    std::ifstream file;
    
    file.open(argv[1]);
    if (!file.is_open()){
        std::cout << "Unable to open file"; 
        return EXIT_FAILURE;
    }
    
    int count = 0;
    int negative = 0; // -
    int point1 = 0; // 9.9
    int point2 = 0; // 99.9
    int nopoint1 = 0; // 9
    int nopoint2 = 0; // 99

    while ( std::getline (file,name,';') ){
             
        getline(file,string_temp);
        
        const char* in = string_temp.c_str();
        int idx = 0;
        
        count++;
    
        if (in[0] == '-'){
            negative++;
        }
        
        if (in[idx+1] == '.') {
            point1++;
        } else if (in[idx+2] == '.') {
            point2++;
        } else if (in[idx+1] == '\0') {
            nopoint1++;
        } else {
            nopoint2++;
        }
        
    }
    file.close();  
    
    std::cout << "count: " << count << '\n';
    std::cout << "negative: " << negative << '\n';
    std::cout << "point1: " << point1 << '\n';
    std::cout << "point2: " << point2 << '\n';
    std::cout << "no point1 " << nopoint1 << '\n';
    std::cout << "no point2 " << nopoint2 << '\n';
    
    return EXIT_SUCCESS;
}

