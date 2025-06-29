#include "solver.h"
#include "tools.h"
#include <vector>
#include <cmath>
#include <stdexcept> 
using namespace std;

// Function to construct Q
vector<vector<double>> PortfolioSolver::buildQ (const vector<vector<double>>& CovMat,
                                                const vector<double>& meanRet) const
{
    // Initializing a Vector of 1s (e)
    vector<double> e(numberAssets, 1.0);
    // Intializing matrix Q
    int dim = getDim();
    vector<vector<double>> Q(dim, vector<double>(dim, 0.0));

    // Adding the Covariance Matrix to Q
    for (int i=0; i<numberAssets; i++){
        for (int j=i; j<numberAssets; j++){
            Q[i][j] = CovMat[i][j];
            Q[j][i] = CovMat[i][j]; //Symmetry
        }
    }
    // Adding -R and -e
    for (int i=0; i<numberAssets; i++){
        Q[i][numberAssets] = -meanRet[i];
        Q[i][numberAssets+1] = -e[i];
        Q[numberAssets][i] = -meanRet[i]; // Symmetry
        Q[numberAssets+1][i] = -e[i]; // Symmetry
    }
    // Adding regularizing term 
    /*for (int i = 0; i < dim; ++i){
        Q[i][i] += 1e-4;}*/

    return Q;
}

// Function to construct x
vector<double> PortfolioSolver::initialX() const
{
    int dim = getDim(); 
    vector<double> x(dim, 0.0);  // initialize all to 0

    double equalw = 1.0 / numberAssets;
    for (int i = 0; i < numberAssets; ++i) {
        x[i] = equalw;  // equal weight for assets only
    }
    return x;
}

// Function to construct b
vector<double> PortfolioSolver::buildB() const
{
    int dim = getDim();
    vector<double> b(dim, 0.0);
    b[numberAssets] = -target_ret;
    b[numberAssets+1] = -1.0;
    return b;
}

// Function to solve the Conjugate Gradient Method
vector<double> PortfolioSolver::solvebyCGM(vector<vector<double>>& Q,
                                            vector<double>& x, vector<double>& b,
                                            const int max_iter, const double tol)
{
    // Initializing the required variables
    int dim = getDim();
    vector<double> Qx = Tools::matMultVec(Q, x);        // Q*x0
    vector<double> s(dim);                              // s0

    // s0 = b - Qx0
    for (int i=0; i<dim; i++){
        s[i] = b[i] - Qx[i];
    }
    vector<double> p = s;                               // p0=s0
    vector<double> Qp(dim, 0.0);                        // To store Q * p 
    double alpha, beta, s_old_sq, s_new_sq;
    
    // Running the loop
    for (int iter=0; iter<=max_iter; iter++){
        // Compute Alpha
        s_old_sq = Tools::dotProduct(s,s);              //S_k' * S_k
        Qp = Tools::matMultVec(Q,p);                    // Q * P_k
        double denom = Tools::dotProduct(p, Qp);

        // Adding safeguard for denominator
        if (fabs(denom) < 1e-20)
        {throw runtime_error("Division by zero error: denominator in alpha computation is zero");}

        alpha = s_old_sq / denom;                       // alpha_k = S_K'*S_k / P_k' * Q * P_k

        // Update the solution (weights) & compute new residual
        for(int i=0; i<dim; i++){
            x[i] += alpha*p[i];                         // x_k+1 = x_k + alpha_k * p_k
            s[i] -= alpha*Qp[i]; 
        }

        // Compute square to determine if below tolerance
        s_new_sq = Tools::dotProduct(s,s);
        if(s_new_sq <= tol) break;
        
        // Computing Beta
        beta = s_new_sq / s_old_sq;

        // Getting new direction
        for(int i=0; i<dim; i++){
            p[i] = s[i] + beta*p[i];                    //p_k+1 = s_k+1 + beta_k * p_k
        }
    }
    return x;
}

