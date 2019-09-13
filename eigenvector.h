#ifndef _EIGENVECTOR_
#define _EIGENVECTOR_
#include "includes.h"
#include "calculation_partial_choice.h"
#include "find_solution.h"
#include "qr.h"
double norm(vector<double> sol);
double norm_delta(vector<double> sol1, vector<double> sol2);
vector<double> product(const vector<double> &vec, const vector<vector<double>> &matrix);
vector<vector<double>> find_eigenvector(vector<vector<double>> &matrix, vector<double> &eigenvalues);

#endif