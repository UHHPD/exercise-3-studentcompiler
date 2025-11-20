#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


double poisson(double mu,int k) {
        double p1 = pow(mu, k);
        double p2 = 1/exp(mu);
        double p3 = 1/tgamma(k+1);
        double poissonProbability = p1*p2*p3;
        return poissonProbability;
    }

int main() {
    using namespace std;

    int N = 234;
    double zahl;
    int i = 0;
    vector<int> daten;
    double mean = 3.11538;
    double Likelihood_mean = 1;
    double Likelihood_ratio= 1;
    vector<double> mu;

    ifstream fin("datensumme.txt");

    while (fin >> zahl && i < N) {
        daten.push_back(zahl);
        i++;
    }
    fin.close();

    for (int k: daten)
    Likelihood_mean *= poisson(mean, k);
    cout << "the likelihood for μ = 3.11538 is " << Likelihood_mean << endl;

    double LM = 1;
    double stepsize = 0.1;
    double mu_max = 6;

    for (int i = 0 ; i <= 60; i++){
        double m = i * stepsize;
        mu.push_back(m);
    }

    ofstream fout1("likelihood.txt");
    ofstream fout2("nll.txt");
    ofstream fout3("deltanll.txt");

    for (double j: mu)
    {
        double Likelihood_mu = 1;
        for (int k: daten)
        {
            Likelihood_mu *= poisson(j, k);
        }
        //cout << j << " " << Likelihood_mu << endl;

        double nll = -2*log(Likelihood_mu);
        double delta_nll = 2*log(Likelihood_mean) - 2*log(Likelihood_mu);
        fout1 << j << " " << Likelihood_mu << endl;
        fout2 << j << " " << nll << endl;
        fout3 << j << " " << delta_nll << endl;
        
    }
    fout1.close();
    fout2.close();
    fout3.close();

    for (int k: daten)
    Likelihood_ratio *= poisson(mean,k)/poisson(k, k);

    cout << "the likelihood ratio Λ " << -2*log(Likelihood_ratio) << endl;
    double z = (-2*log(Likelihood_ratio)-233)/sqrt(2*233);
    cout << "the relative deviation " << z << endl;
}