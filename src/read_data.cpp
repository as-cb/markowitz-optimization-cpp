#include "read_data.h"
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include "csv.h"

double string_to_double( const std::string& s )
{
	std::istringstream i(s);
	double x;
	if (!(i >> x))
		return 0;
	return x;
} 
 
void readData(double **data, std::string fileName)
{
	char tmp[20];
	ifstream file (strcpy(tmp, fileName.c_str()));
	Csv csv(file);
	string line;
	if (file.is_open())
	{
		int i=0;
		while (csv.getline(line) != 0) {
         	for (int j = 0; j < csv.getnfield(); j++)
            {
               double temp=string_to_double(csv.getfield(j));
               //cout << "Asset " << j << ", Return "<<i<<"="<< temp<<"\n";
               data[j][i]=temp;
            }
            i++;
		}
		
		file.close();
	}
	else {cout <<fileName <<" missing\n";exit(0);}
                                                                 }

void writeToCSV(const vector<vector<vector<double>>>& results,
                       const vector<double>& target_returns,
                       const string& filename) {
    ofstream outFile(filename);

    outFile << "Target Return,Iteration,OOS Mean,OOS Variance\n";

    for (size_t i = 0; i < target_returns.size(); ++i) {
        for (size_t j = 0; j < results[i].size(); ++j) {
            outFile << fixed << setprecision(6)
                    << target_returns[i] << ","
                    << j + 1 << ","
                    << results[i][j][0] << ","
                    << results[i][j][1] << "\n";
        }
    }

    outFile.close();
    cout << "Results written to " << filename << endl;
}


                                                                    
