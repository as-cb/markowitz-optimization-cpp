#include "tools.h"
#include "solver.h"
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

Tools::Tools (double** returnMatrix, int assets, int start_, int end_) 
    : matrix(returnMatrix), numberAssets(assets), start(start_), end(end_){}

double Tools::Mean (int assetIndex)const{
    if (start >= end) return 0.0;
    double sum=0.0;
    for (int i=start;i<end;i++){
        sum += matrix[assetIndex][i];
    }
    return sum/(end-start); 
}

double Tools::Cov (int asset1, int asset2)const{
    if (start >= end) return 0.0;
    double covsum=0.0;
    double mean1 = Mean(asset1);
    double mean2 = Mean(asset2);
    // Looping through the range to calculate numerator
    for (int i=start; i<end; i++){
        double diff1 = matrix[asset1][i] - mean1;
        double diff2 = matrix[asset2][i] - mean2;
        covsum += diff1 * diff2;
    }
    return covsum/(end-start-1);
}

vector<vector<double>> Tools::CovMatrix ()const{
    //Creating a square matrix to hold all the convariances
    vector<vector<double>> covmat(numberAssets,
        vector<double>(numberAssets, 0.0));
    // Calculating and storing all the covariances 
    for (int i=0; i<numberAssets; i++){
        for (int j=i; j<numberAssets; j++){
            double covij = Cov(i,j);
            covmat[i][j] = covij;
            covmat[j][i] = covij; //symmetry
        }
    }
    return covmat;
}

//Creating a function to calculate the mean vector
vector<double> Tools::meanVec ()const{
    // Initializing a vector to store the mean returns
    vector<double> meanRet(numberAssets, 0.0);
    for (int i=0; i<numberAssets; i++){
        meanRet[i] = Mean(i);
    }
    return meanRet;
}

vector<double> Tools::matMultVec (const vector<vector<double>>& mat, 
                                    const vector<double>& vec)
{
    int rows = mat.size();
    int cols = mat[0].size();
    // Checking whether matrix columns == vector rows
    if (cols != vec.size() || rows == 0) return {};  // or throw an error
    vector<double> result(rows, 0.0);

    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            result[i] += mat[i][j] * vec[j];
        }
    }
    return result;
}

double Tools::dotProduct (const vector<double>& vec1, const vector<double>& vec2)
{
    if (vec1.size() != vec2.size()) return 0.0;
    int rows = vec1.size();
    double result = 0.0;
    // Looping through the vectors 
    for (int i=0; i<rows; i++){
        result += vec1[i] * vec2[i];
    }
    return result;
}
