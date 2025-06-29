#ifndef solver_h
#define solver_h
#include <vector>
//using namespace std;

class PortfolioSolver{
    private:
    int numberAssets; //Number of assets
    double target_ret; //Target return

    public:
    // Constructor
    PortfolioSolver(int assets, double target) 
    : numberAssets(assets), target_ret(target) {}

    int getDim() const { return numberAssets + 2; }

    std::vector<std::vector<double>> buildQ (const std::vector<std::vector<double>>& CovMat,
                                    const std::vector<double>& meanRet) const;
    std::vector<double> initialX() const;
    std::vector<double> buildB() const;
    std::vector<double> solvebyCGM(std::vector<std::vector<double>>& Q,
                          std::vector<double>& x, std::vector<double>& b,
                          const int max_iter = 1000, const double tol = 1e-6);

};


#endif 