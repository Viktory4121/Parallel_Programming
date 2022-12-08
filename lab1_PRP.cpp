#include<iostream>
#include<random>
#include<vector>
#include<float.h>
#include<math.h>
#include<thread>
#include<future>
#include<time.h>
#include<ppltasks.h> //для создания динамического добавления потоков

using namespace std;

class MonteCarlo {

    int N;              //количество итераций
    int eps;            //генерация внутри заданной границы от -eps до eps
    int k;              //количество переменных

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
        double f = 0;

        for (int i = 0; i < this->k; i++) {
            f = (double)rand() / RAND_MAX;
            x.push_back(min_ + f * (max_ - min_));
        }
        return x;
    }

    void cycle_method(int N, double f, promise <double[3]> xi) {
        double fi, f_min = f;
        vector<double> x_min;
        vector<double> x;
        int i = 0;
        x = randomPoint();

        while (i < N) {
            x = randomPoint();
            fi = function(x);

            if (fi < f_min) {
                x_min = x;
                f_min = fi;
            }
            i++;
        }
        xi.set_value(x);
    }

    vector<double> method() {
        double f_min = DBL_MAX;
        vector<double> xi1, xi2, xi;
        int count = this->N;
        promise <double[3]> xi1, xi2;
        future <double[3]> c_m1 = xi1.get_future(), c_m2 = xi2.get_future();

        thread t1(cycle_method, count / 2, f_min, move(xi1));
        thread t2(cycle_method, count - count/2, f_min, move(xi2));

        c_m1.get();
        c_m2.get();
        //thread t1([&]() { cycle_method(count / 2, f_min, move(xi1)); });
        //thread t2([&]() { cycle_method(count - count / 2, f_min, move(xi2)); });
        t1.join();
        t2.join();

        //vector<double> xi = cycle_method(count, f_min, xi);

        if (function(xi1) <= function(xi2)) xi = xi1;
        else xi = xi2;

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

    cout << "\nTime: " << seconds << " s";

}
