#include<iostream>
#include<random>
#include<vector>
#include<float.h>
#include<math.h>
//#include<stdio.h> 
#include<time.h> 
//#include <chrono>

using namespace std;

class MonteCarlo {

    int N;              //количество итераций
    int eps;            //количество итераций
    int k;              //количество итераций

public:

    MonteCarlo(int number, int epsilon, int elem) {
        N = number;
        eps = epsilon;
        k = elem;
    }

    vector<double> randomPoint() {
        vector <double > x;
        int min_ = -this->eps;
        int max_ = this->eps;

        for (int i = 0; i < this->k; i++) {
            double f = (double)rand() / RAND_MAX;
            x.push_back(min_ + f * (max_ - min_));
        }
        return x;
    }

    vector<double> method() {
        double f_min = DBL_MAX, fi;
        vector<double> x_min, xi;
        int i = 0;

        while (i < this->N) {
            xi = randomPoint();
            fi = function(xi);
            
            if (fi < f_min) {
                x_min = xi;
                f_min = fi;
            }
            i++;
        }

        return xi;
    }

    double function(vector<double> x) {

        return (pow(1.5 - x[0] + x[0] * x[1], 2)
            + pow(2.25 - x[0] + pow(x[0] * x[1], 2), 2)
            + pow(2.625 - x[0] + pow(x[0] * x[1], 3), 2));
    }
};


int main() {
    clock_t start = clock();
    //auto begin = chrono::steady_clock::now();

    int count_iter = 10000000;
    int epsilon = 10;
    int count_var = 2;

    MonteCarlo mc = MonteCarlo(count_iter, epsilon, count_var);
    vector<double> rezult_x = mc.method();
    double rezult_f = mc.function(rezult_x);

    cout << "X_opt: ";
    for (int i = 0; i < count_var; i++) {
        cout << rezult_x[i] << " ";
    }
    cout << "\nF(X_opt): " << rezult_f;

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //auto end = std::chrono::steady_clock::now();
    //auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    cout << "\nTime: " << seconds << " s";
    //cout << "\nTime: " << elapsed_ms.count() << " ms";

}
