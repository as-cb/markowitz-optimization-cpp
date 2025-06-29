# markowitz-optimization-cpp
This project aims to implement the Markowitz portfolio optimization exercise for a given vector of target returns, and uses the Conjugate Gradient Method (CGM) to do the same. The entire project was written and executed in C++, and Python was used to display the results.

Use the commands below to run and execute the entire program:
g++ -c csv.cpp read_data.cpp main.cpp
g++ -c tools.cpp solver.cpp backtest.cpp
g++ -o ps3 csv.o read_data.o main.o tools.o solver.o backtest.o
./ps3
