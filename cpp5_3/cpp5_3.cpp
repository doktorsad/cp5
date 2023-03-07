#include <iostream>
#include <vector>

class DivideThree {
private:
    std::vector<int> var;
    int sum;
    int count;
public:
    DivideThree() = default;
    DivideThree(const DivideThree& other) = delete;
    DivideThree& operator= (const DivideThree& oyher) = delete;
    void push(const int i) { var.push_back(i); }
    void operator() () {
        for (size_t idx_i = 0; idx_i < var.size(); ++idx_i) {
            if (var[idx_i] % 3 == 0 && var[idx_i] != 0) {
                ++this->count;
                this->sum += var[idx_i];
            }
        }
    }
    int get_sum()const { return this->sum; }
    int get_count() const { return this->count; }
    int get_size() const { return this->var.size(); }
    int get_num(const int idx_i) const { return var[idx_i]; }
    friend std::ostream &operator<< (std::ostream& out, const DivideThree& var) {
        for (size_t idx_i = 0; idx_i < var.get_size(); ++idx_i)
            out << var.get_num(idx_i) << '\t';
        out << '\n';
        return out;
    }
};

int main() {
    int size = 10;
    DivideThree dt;
    for (size_t idx_i = 0; idx_i < size; ++idx_i) {
        dt.push(idx_i);
    }
    std::cout << dt;
    dt();
    std::cout << dt.get_sum() << '\t' << dt.get_count() << '\n';
}