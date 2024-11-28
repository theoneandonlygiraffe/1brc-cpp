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

inline int ctoi(char& c){ 
    return (int) c - '0';
}

inline char itoc(int& i){
    return (char) i + '0';
}

void char_to_int(char* c, int& i){
    i = ctoi(c[4]);
    i = i + (ctoi(c[2]) * 10);
    i = i + (ctoi(c[1]) * 100);
    /*
    if (c[0] == '-') {
        i = i * -1;
    }
    */
    i = i * (1 - 2 * (c[0] == '-'));
}

void int_to_char(int i, char* c){
    int b1;
    int b10;
    int b100;
    
    /*
    if(i < 0){
        c[0] = '-';
        i = i * -1;
    } else {
        c[0] = ' ';
    }
    */
    
    c[0] = ('-' * (char) ((i >> 31) & 1)) + (' ' * (char) (1 - ((i >> 31) & 1)));
    i = (i + (i >> 31)) ^ (i >> 31);
    
    b1 = i % 10;
    b10 = (i % 100) / 10;
    b100 = (i % 1000) / 100;
    
    c[1] = itoc(b100);
    c[2] = itoc(b10);
    c[3] = '.';
    c[4] = itoc(b1);
}

// 0 1 2 3 4
// - 9 9 . 9

void pad_number(const char* in , char* out){
    
    
    /*
    if (in[0] == '-'){
        out[0] = '-';
        idx++;
    } else {
        out[0] = '0';
    }
    */
    
    out[0] = ((in[0] == '-') * '-'); // else is irrelevant
    int idx = 0;
    idx = 1 * (in[0] == '-');
    
    out[3] = '.';
    
    const char& in0 = in[idx];
    const char& in1 = in[idx+1];
    const char& in2 = in[idx+2];
    const char& in3 = in[idx+3];
    
    
    out[1] = (char) ('0' * (( in1 == '.' ) + ( in1 == '\0' ))) + (in0 * (( in2 == '.' ) + ( in2 == '\0' )));
    out[2] = (char) (in0 * (( in1 == '.' ) + ( in1 == '\0' ))) + (in1 * (( in2 == '.' ) + ( in2 == '\0' )));
    out[4] = (char) ('0' * (in1 == '\0')) + (in2 *  ( in1 == '.' ))  + (in3 *  ( in2 == '.' ));
    
    /*
    out[1] = ('0' * (in1 == '.' || in1 == '\0')) + (in0 * (in1 != '.' && in1 != '\0'));
    out[2] = (in0 * (in1 == '.' || in1 == '\0')) + (in1 * (in2 == '.' || in2 == '\0'));
    out[4] = ('0' * (in1 == '\0')) + (in2 * (in1 == '.')) + (in3 * (in2 == '.'));
    */
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
        
        data& d = map[name];
        d.sum = d.sum + temp;
        d.n = d.n + 1;
        if ( d.min > temp ){
            d.min = temp;
        }
        if ( d.max < temp ){
            d.max = temp;
        }

    }
    file.close();
    
    for (const auto& element: map){
        std::string name = element.first;
        const data& d = element.second;
        char min[6];
        char mid[6];
        char max[6];
        
        min[5] ='\0';
        mid[5] ='\0';
        max[5] ='\0';
        
        int_to_char(d.min, min);
        int_to_char((d.sum/d.n), mid);
        int_to_char(d.max, max);
        
        
        std::cout << name << '=' << min << '/' << mid << '/' << max << '\n';
    }
    
    return EXIT_SUCCESS;
}

