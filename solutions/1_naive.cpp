#include <iostream>
#include <fstream>
#include <string>
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
    
    while ( std::getline (file,name,';') ){
        getline(file,string_temp);
        float temp = std::stof(string_temp);
        std::cout << name << '\n';
        std::cout << temp << '\n';

    }
    file.close();
    
    return EXIT_SUCCESS;
}

