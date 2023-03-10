#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <string>

class DivideThree {
private:
    int sum = 0;
    int count = 0;
public:
    DivideThree() = default;
    ~DivideThree() = default;
    void operator() (const int i) {
        if ((i % 3) == 0) {
            sum += i;
            ++count;
        }
    }
    int get_sum()const { return this->sum; }
    int get_count() const { return this->count; }
    void out_DivideThree(const std::string &str) const {
        std::cout << str <<" count: " << get_count() <<
            " sum: " << get_sum() << std::endl;
    }
};

template <class T>
void out_print(const T& var,const std::string &str) {
    std::cout << str << ": ";
    for (const auto& i : var)
        std::cout << i << '\t';
    std::cout << std::endl;
}

int main() {
    DivideThree sum_vec;
    DivideThree sum_arr;
    std::string str_vec = "vec";
    std::string str_arr = "arr";
    std::vector<int> vec = { 1,2,3,4,5,6,7,8,9 };
    std::array<int, 9> arr = { 11,22,33,44,55,66,77,88,99 };
    out_print(vec, str_vec);
    out_print(arr, str_arr);
    sum_vec = std::for_each(vec.begin(), vec.end(), sum_vec);
    sum_arr = std::for_each(arr.begin(), arr.end(), sum_arr);
    sum_vec.out_DivideThree(str_vec);
    sum_arr.out_DivideThree(str_arr);
}