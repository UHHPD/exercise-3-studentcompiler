#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double poisson(double mu, int k) {
    double p1 = pow(mu, k);
    double p2 = 1/exp(mu);
    double p3 = 1/tgamma(k+1);
    double poissonProbability = p1*p2*p3;
    return poissonProbability;
}

int main() {
    using namespace std;
    vector<int> zaehler(11);

    ifstream fin("datensumme.txt");

    int N = 234;
    double mean = 3.11538;

    int n_i;

    for(int i = 0 ; i < N ; ++i) {
        fin >> n_i;
        for (int zahl = 0; zahl < 11; zahl++){
            if (n_i == zahl) {
                zaehler[zahl] += 1;
            }
        }
    }
    fin.close();

    ofstream fout1("hist.txt");
    ofstream fout2("histpoi.txt");

    for(unsigned int k = 0 ; k < zaehler.size() ; ++k) {
        fout1 << k << " " << zaehler[k] << "\n";
        double poissonDistr = N * poisson(mean,k);
        fout2 << k << " " << zaehler[k] << " " << poissonDistr << "\n";
        //cout << k << ":" << zaehler[k] << " " << poissonDistr << endl;
    }
}