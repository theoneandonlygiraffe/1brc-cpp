#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdlib.h> 

struct data {
    float sum = 0;
    float n = 0;
    float min = 99.9f;
    float max = -99.9f;
};

int main(int argc , char* argv[] ){
    std::string name;
    std::string string_temp;
    std::ifstream file;
    
    std::map<std::string, data> map;
    
    file.open(argv[1]);
    if (!file.is_open()){
        std::cout << "Unable to open file"; 
        return EXIT_FAILURE;
    }
    
    while ( std::getline (file,name,';') ){
        getline(file,string_temp);
        float temp = std::stof(string_temp);
        
        data& d = map[name];
        d.sum = d.sum + temp;
        d.n = d.n + 1;
        if ( d.min > temp ){
            d.min = temp;
        }
        if ( d.max < temp ){
            d.max = temp;
        }
        
        
        
        //std::cout << name << '\n';
        //std::cout << temp << '\n';

    }
    file.close();
    
    for (const auto& element: map){
        std::string name = element.first;
        const data& d = element.second;
        std::cout << name << '=' << d.min << '/' << d.sum/d.n << '/' << d.max << '\n';
    }
    
    return EXIT_SUCCESS;
}

