#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<string>
#include<sstream>
#include<fstream>

void check_float(float x);
std::string floating_point(float value);

#define MANTISSA_MASK 0x7FFFFF //last 23 bits 0111 1111 1111 1111 1111 1111 -> 7fffff
#define EXPONENT_MASK 0xFF //2-8 bits 
#define MANTISSA_LENGTH 23
#define SIGN_MASK 0x8FFFFFFF

union float_bits{
    float f;
    int f_bit;
};
typedef union float_bits FLOAT;

void check_float(float x){
    FLOAT check;
    check.f = x;

    int t = check.f_bit;
    
    std::cout << "Value -> " <<check.f << std::endl;
    std::cout << "Bit Representation -> "; 
    
    for(int i=31; i>=0; i--){
        uint32_t in = pow(2,i);
        if((t & in) == 0)
            std::cout << 0;
        else
            std::cout << 1; 
    }   std::cout << std::endl;
}

std::string floating_point(float value){
    FLOAT new_float_bits;
    int sign_bit, exponent_bits, mantissa_bits;

    new_float_bits.f = value;

    mantissa_bits = new_float_bits.f_bit & MANTISSA_MASK;
    exponent_bits = (new_float_bits.f_bit >> MANTISSA_LENGTH) & EXPONENT_MASK;
    sign_bit = new_float_bits.f_bit & SIGN_MASK;

    std::ostringstream str_stream;
    std::string ret_str;

    if(sign_bit == 1)
        str_stream << "-";

    if(exponent_bits == 0){
        str_stream << "0.";
        if(mantissa_bits == 0)
            exponent_bits += 1;
    }   else
            str_stream << "1.";

    for(int i = MANTISSA_LENGTH-1; i>=0; i--){
        if( (mantissa_bits & (int)pow(2,i)) == 0)
            str_stream << "0";
        else
            str_stream << "1";
    }   str_stream << " * ";

    if(exponent_bits != 0 || mantissa_bits != 0){
        str_stream << "2^" << exponent_bits - 127;
    }

    ret_str = str_stream.str();
    std::cout << "Outcome -> " << ret_str << std::endl;

    return ret_str;
}

int main(){

    FILE* input = fopen("problem1_data/floating.2.in","r");
    std::ifstream output("problem1_data/floating.2.out");
    int n;
    float f;
    std::string check1;
    std::string check2;

    fscanf(input,"%d",&n);

    for(int i=0; i<n; i++){
        fscanf(input,"%f", &f);
        check_float(f);

        std::getline(output, check1);
        check2 = floating_point(f);

        if(check1 == check2)
            std::cout << "Output Matched\n\n";
        else
            std::cout << "Output Mismatched\n\n";
    }
    fclose(input);
    
    return 0;
}