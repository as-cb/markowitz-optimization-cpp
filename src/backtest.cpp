#include "tools.h"
#include "solver.h"
#include "backtest.h"
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

Backtest::Backtest (double** returnMatrix, int assets, int time,
                const vector<double>& target_vec, int insample, int outsample)
    : matrix(returnMatrix), numberAssets(assets), numberReturns(time), 
    target_vector(target_vec), is_window(insample), os_window(outsample) {} 


// Writing the loop for rolling window and backtesting
vector<vector<double>> Backtest::rollingWindow (double target_return)
{
    // Initializing matrix to store OOS statistics
    vector<vector<double>> oosStats;
    // Starting the main rolling window loop
    for (int i=0; i + is_window + os_window <= numberReturns; i+=os_window)
    {
        // Intializing variables for CGM solver
        // Computing In-sample statistics using Tools class
        Tools is_stats(matrix, numberAssets, i, i + is_window);
        vector<vector<double>> is_covmat = is_stats.CovMatrix();
        vector<double> is_mean = is_stats.meanVec();
        
        // Computing optimal weights in-sample using PortfolioSolver class
        PortfolioSolver port(numberAssets, target_return);
        vector<vector<double>> Q = port.buildQ(is_covmat, is_mean); // Building Q
        vector<double> x = port.initialX();                         // Building X
        vector<double> b = port.buildB();                           // Building B
        vector<double> weights = port.solvebyCGM(Q, x, b);          // Getting optimal weights
        // Removing the last two values (lambda and mu)
        weights.pop_back();
        weights.pop_back();

        // Conducting backtesting
        double portmean, portvar;
        // Computing Out-of-sample stats using Tools class
        Tools os_stats(matrix, numberAssets, i + is_window, i + is_window + os_window);
        vector<double> os_mean = os_stats.meanVec();
        vector<vector<double>> os_covmat = os_stats.CovMatrix();

        // Calculating OOS Portfolio mean and variance
        portmean = Tools::dotProduct(os_mean, weights);
        vector<double> temp = Tools::matMultVec (os_covmat, weights);
        portvar = Tools::dotProduct (weights, temp);

        // Appending results to results matrix
        oosStats.push_back({portmean, portvar});
    }
    return oosStats;
}

vector<vector<vector<double>>> Backtest::backtestResults ()
{
    vector<vector<vector<double>>> finalResult;

    // Looping through all the target returns
    for (double targets : this->target_vector){
        vector<vector<double>> interResult = this->rollingWindow(targets);
        finalResult.push_back(interResult);
    }
    return finalResult;
}

vector<double> Backtest::targetVector (double start, double end, double increment)
{
    // Initializng the results vector
    vector<double> result;
    // Appending the first target
    double temp = start + increment, epsilon = 1e-6;
    // Running a loop to append the other targets
    while (temp <= end + epsilon){
        result.push_back(temp);
        temp += increment;
    }
    return result;
}
