#include <iostream>

class MyException : std::exception {
private:
    std::string whatStr;
public:
    MyException(std::string&& whatStr) noexcept : whatStr(std::move(whatStr)) {}
    MyException(const std::string& whatStr) noexcept : whatStr(whatStr) {}
    ~MyException() noexcept = default;

    const char* what() const noexcept override {
        return whatStr.c_str();
    }
};

template<typename T>
class BivariateArr {
private:
    int col;
    int row;
    T** arr;
public:
    BivariateArr(const int col, const int row) : col(col), row(row) {
        arr = new T * [col];
        for (size_t idx_i = 0; idx_i < col; ++idx_i)
            arr[idx_i] = new T[row];
        for (size_t idx_i = 0; idx_i < col; ++idx_i) {
            for (size_t idx_k = 0; idx_k < row; ++idx_k) {
                arr[idx_i][idx_k] = 0;
            }
        }
    }
    ~BivariateArr() {
        for (size_t idx_i = 0; idx_i < col; ++idx_i) {
            delete[] arr[idx_i];
        }
        delete[] arr;
    }
    BivariateArr(const BivariateArr& other) = delete;
    BivariateArr& operator= (const BivariateArr& other) = delete;
    bool at_col(int col_i) {
        if (col_i < col && col_i >= 0)
            return true;
        return false;
    }
    const bool at_col(int col_i) const {
        if (col_i < col && col_i >= 0)
            return true;
        return false;
    }

    class Proxy {
    public:
        Proxy(T* array, int row_pr) : array(array), row_pr(row_pr) {}
        ~Proxy() = default;
        T &operator[] (int index) {
            if (!at(index))
                throw MyException("the second index was passed incorrectly");
            return array[index];
        }
        const T operator[] (int index) const {
            if (!at(index))
                 throw MyException("the second index was passed incorrectly");
            return array[index];
        }
    private:
        bool at(int idx_i) {
            if (idx_i < row_pr && idx_i >= 0)
                return true;
            return false;
        }
        const bool at(int idx_i) const {
            if (idx_i < row_pr && idx_i >= 0)
                return true;
            return false;
        }
        int row_pr;
        T* array;
    };

    Proxy operator[](int idx_i) {
        if (!at_col(idx_i))
             throw MyException("the first index was passed incorrectly");
        return Proxy(arr[idx_i], row);
     
    }

    const Proxy operator[](int idx_i) const {
        if (!at_col(idx_i))
             throw MyException("the first index was passed incorrectly");
        return Proxy(arr[idx_i], row);
    }
};

// Просмотренно много форумов, говорят проще реализовать оператор(), мб есть способ лучше?

int main() {
    try{
        const int x = 1;
        BivariateArr<int> arr(1, 5);
        arr[0][0] = x;
        arr[0][1] = 2;
        arr[0][6] = 1;
        std::cout << arr[0][0] << arr[0][1] << std::endl;
        return 0;
    }
    catch (const MyException& ex) {
        std::cout << ex.what() << std::endl;
    }
}