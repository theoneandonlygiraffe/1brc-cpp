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

int ctoi(char c){
    switch (c){
        case '0' : return 0;
        break;
        case '1' : return 1;
        break;
        case '2' : return 2;
        break;
        case '3' : return 3;
        break;
        case '4' : return 4;
        break;
        case '5' : return 5;
        break;
        case '6' : return 6;
        break;
        case '7' : return 7;
        break;
        case '8' : return 8;
        break;
        case '9' : return 9;
        break;
    }
}

char itoc(int i){
    switch (i){
        case 0 : return '0';
        break;
        case 1 : return '1';
        break;
        case 2 : return '2';
        break;
        case 3 : return '3';
        break;
        case 4 : return '4';
        break;
        case 5 : return '5';
        break;
        case 6 : return '6';
        break;
        case 7 : return '7';
        break;
        case 8 : return '8';
        break;
        case 9 : return '9';
        break;
    }
}

void char_to_int(char* c, int& i){
    //int i;
    i = ctoi(c[4]);
    i = i + (ctoi(c[2]) * 10);
    i = i + (ctoi(c[1]) * 100);
    if (c[0] == '-') {
        i = i * -1;
    }
    //return i;
}

void int_to_char(int i, char* c){
    if(i < 0){
        c[0] = '-';
    } else {
        c[0] = '0';
    }
    //TODO
}

// 0 1 2 3 4
// - 9 9 . 9

void pad_number(const char* in , char* out){
    int idx = 0;
    
    if (in[0] == '-'){
        out[0] = '-';
        idx++;
    } else {
        out[0] = '0';
    }
    
    if (in[idx+1] == '.') {
        out[1] = '0';
        out[2] = in[idx];
      out[3] = '.';
        out[4] = in[idx+2];
    } else if (in[idx+2] == '.') {
        out[1] = in[idx];
        out[2] = in[idx+1];
      out[3] = '.';
        out[4] = in[idx+3];
    } else if (in[idx+1] == '\0') {
        out[1] = '0';
        out[2] = in[idx];
      out[3] = '.';
        out[4] = '0';
    } else {
        out[1] = in[idx];
        out[2] = in[idx+1];
      out[3] = '.';
        out[4] = '0';
    }
}

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
        
        char padded_number[6];
        int temp;
        padded_number[5] ='\0';
        
        getline(file,string_temp);
        pad_number(string_temp.c_str(),padded_number);
        char_to_int(padded_number, temp);
        //std::cout << padded_number << '=' << temp << '\n';
        
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

