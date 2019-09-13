#ifndef _ZEYDEL_RELAXATION_
#define _ZEYDEL_RELAXATION_

#include "includes.h"

using namespace std;
vector<double> zeydel_relax_solution(double parametr, std::vector<std::vector<double>> &matrix_zeydel, vector<double> &changed_vector_zeydel, double norm_B, double &parametr_apost);
double norm_up_triangle(std::vector<std::vector<double>> &matrix);

#endif