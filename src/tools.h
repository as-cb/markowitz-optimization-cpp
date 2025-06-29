#ifndef tools_h
#define tools_h
#include <vector>
using namespace std;

class Tools 
{
    private:
    double** matrix;
    int numberAssets;
    int start;
    int end;

    public:
    // Constructor
    Tools (double** returnMatrix, int assets, int start_, int end_);

    double** getReturns() {return matrix;}
    int getAssets() const {return numberAssets;}
    int getStart() const {return start;}
    int getEnd() const {return end;}

    double Mean (int assetIndex)const;
    double Cov (int asset1, int asset2)const;
    vector<vector<double>> CovMatrix()const;
    vector<double> meanVec()const;
    
    // Static functions
    static vector<double> matMultVec (const vector<vector<double>>& mat,
                                        const vector<double>& vec);
    static double dotProduct (const vector<double>& vec1, const vector<double>& vec2);
};

#endif
