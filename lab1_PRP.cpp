#include<iostream>
#include<random>
#include<vector>

using namespace std;

template<typename T>
class MonteCarlo{
    vector<T> point0;   //начальная точка
    int N;              //количество итераций
    double eps;         //количество итераций
    int k;              //количество итераций

    MonteCarlo () {
        
    }

public:
    vector<T> randomPoint() {
        vector<T> x;
        int min_ = -this->eps;
        int max_ = this->eps;
        for (int i = 0; i < this->k; i++) {
            x.push_back(rand() % max_ + min_);
        }
        return x;
    }

    vector<T> method() {
        
    }
};

template<typename T>
double function(vector<T> x) {

    return 0;
}

int main() {
    MonteCarlo<double> rezult;

    std::cout << "Hello World!\n";
}
