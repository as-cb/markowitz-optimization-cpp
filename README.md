# Markowitz Portfolio Optimization in C++

This project aims to implement the **Markowitz portfolio optimization** exercise for a given vector of target returns, and uses the **Conjugate Gradient Method (CGM)** to do the same. The entire project was written and executed in **C++**, and **Python** was used to display the results.

---

## Project Summary

- **Objective**: Minimize portfolio variance for a given target return (mean-variance optimization)
- **Methodology**: 
  - Uses the **Conjugate Gradient Method** to solve the quadratic optimization problem efficiently
  - Processes CSV input data for asset returns and covariances
  - Outputs optimal portfolio weights and backtested performance
- **Languages Used**: 
  - Core Logic: **C++**
  - Plotting and visualization: **Python**

---

## How to Compile and Run

Use the following commands in your terminal to compile and execute the program:

```bash
g++ -c csv.cpp read_data.cpp main.cpp
g++ -c tools.cpp solver.cpp backtest.cpp
g++ -o ps3 csv.o read_data.o main.o tools.o solver.o backtest.o
./ps3
