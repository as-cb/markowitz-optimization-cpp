#ifndef backtest_h
#define backtest_h
#include <vector>

class Backtest 
{
    private:
    double** matrix;
    int numberAssets;
    int numberReturns;
    std::vector<double> target_vector;
    int is_window;
    int os_window;

    public:
    // Constructor
    Backtest (double** returnMatrix, int assets, int time,
                const std::vector<double>& target_vec, int insample, int outsample);
    double** getReturns() {return matrix;}
    int getAssets() {return numberAssets;}
    int getFreq() {return numberReturns;}
    std::vector<double> getTarget() {return target_vector;}
    int getTrainingWindow() {return is_window;}
    int getTestingWindow() {return os_window;}

    std::vector<std::vector<double>> rollingWindow(double target_return);
    std::vector<std::vector<std::vector<double>>> backtestResults ();
    static std::vector<double> targetVector(double start, double end, double increment);

};

#endif 