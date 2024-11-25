#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdlib.h> 

struct data {
    float sum;
    float n;
    float min;
    float max;
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
        
        if ( map.contains(name)){
            data& d = map[name];
            d.sum = d.sum + temp;
            d.n = d.n + 1;
            if ( d.min > temp ){
                d.min = temp;
            }
            if ( d.max < temp ){
                d.max = temp;
            }
        } else {
            data d;
            d.sum = temp;
            d.n = 1;
            d.min = temp;
            d.max = temp;
            map[name] = d;
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

