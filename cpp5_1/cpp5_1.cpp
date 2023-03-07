#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

template <typename T>
void fun_pow_templete(T &var){
   var = std::pow(var, 2);
}

template <>
void fun_pow_templete(std::vector<int> &var){
    std::for_each(var.begin(), var.end(), [] (int &i){i = std::pow(i, 2);});
}

template <typename T>
void output_the_value(T &var){
    std::cout << var << std::endl;
}

template <>
void output_the_value (std::vector<int> &var){
    std::for_each(var.begin(), var.end(), [] (const int i){std::cout << i << '\t';});
    std::cout << std::endl;
}

int main(){
    int var_int = 2;
    std::vector<int> var_vec_int {1,2,3,4,5};
    std::cout << "Input:" << std::endl;
    output_the_value(var_int);
    output_the_value(var_vec_int);
    fun_pow_templete(var_int);
    fun_pow_templete(var_vec_int);
    std::cout << "Output:" << std::endl;
    output_the_value(var_int);
    output_the_value(var_vec_int);
    return 0;
}