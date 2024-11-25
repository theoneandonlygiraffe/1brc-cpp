#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <stdlib.h> 

struct data {
    int sum = 0;
    int n = 0;
    int min = 999;
    int max = -999;
};

int main(int argc , char* argv[] ){
    std::string name;
    std::string string_temp;
    std::ifstream file;
    
    std::unordered_map<std::string, data> map;
    
    file.open(argv[1]);
    if (!file.is_open()){
        std::cout << "Unable to open file"; 
        return EXIT_FAILURE;
    }
    
    while ( std::getline (file,name,';') ){
        getline(file,string_temp);
        int temp = (int) (std::stof(string_temp) * 10);
        
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
        std::cout << name << '=' << (float)d.min/10 << '/' << ((float)d.sum/d.n)/10 << '/' << (float)d.max/10 << '\n';
    }
    
    return EXIT_SUCCESS;
}

