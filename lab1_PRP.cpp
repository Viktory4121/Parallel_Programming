#include<iostream>
#include<random>
#include<vector>
#include<float.h>
#include"math.h"

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
            x.push_back(rand() % max_ + min_);
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
    int count_iter = 100000000000000000;
    int epsilon = 10000000;
    int count_var = 2;

    MonteCarlo mc = MonteCarlo(count_iter, epsilon, count_var);
    vector<double> rezult_x = mc.method();
    double rezult_f = mc.function(rezult_x);
    for (int i = 0; i < count_var; i++) {
        cout << rezult_x[i] << " ";
    }
    cout << " " << rezult_f;
}
