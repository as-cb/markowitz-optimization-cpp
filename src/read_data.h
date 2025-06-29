#ifndef read_data_h
#define read_data_h
#include <vector>
#include <string>
#include <iostream>

double string_to_double( const std::string& s );
void readData(double **data, std::string fileName);
void writeToCSV (const std::vector<std::vector<std::vector<double>>>& results,
                        const std::vector<double>& target_returns,
                        const std::string& filename);

#endif