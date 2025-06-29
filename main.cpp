#include "backtest.h"
#include "csv.h"
#include "read_data.h"
#include "solver.h"
#include "tools.h"
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <vector>

// g++ -c csv.cpp read_data.cpp main.cpp
// g++ -c tools.cpp solver.cpp backtest.cpp
// g++ -o ps3 csv.o read_data.o main.o tools.o solver.o backtest.o
// ./ps3

using namespace std;

int main (int argc, char *argv[])
{
    // Defining the dimensions of the entire returns matrix
    int numberAssets = 83;
    int numberReturns = 700;
    // Allocating memory for the matrix
    double **returnMatrix = new double*[numberAssets];
    // Populating the returns for each asset
    for (int i=0; i<numberAssets; i++){
        returnMatrix[i] = new double[numberReturns];
    }
    // Reading the CSV data
    string fileName="asset_returns.csv";
	readData(returnMatrix,fileName);

    //Conducting backtests for a vector of target returns
    vector<double> target_vector = Backtest::targetVector(0.0, 0.1, 0.005);
    int insample_window=100, oos_window=12;

    // Creating portfolios for each target, by solving the linear system using CGM
    Backtest portfolios(returnMatrix, numberAssets, numberReturns, 
                            target_vector, insample_window, oos_window);
    
    // Getting the OOS results for all portfolios (3-D Vector)
    vector<vector<vector<double>>> results = portfolios.backtestResults();

    // Writing the final outputs to a CSV file
    writeToCSV(results, target_vector, "assignment_result.csv");

    // Deleting the return matrix 
    for (int i=0; i<numberAssets; i++){
        delete [] returnMatrix[i];
    }
    delete [] returnMatrix;

    return 0;
}