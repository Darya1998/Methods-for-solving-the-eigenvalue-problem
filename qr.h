#ifndef _QR_
#define _QR_
#include "includes.h"

struct QR_Matrix{
	QR_Matrix(){};
	vector<vector<double>> R;
	vector<vector<double>> T;
	vector<vector<double>> RQ;
};

QR_Matrix qr_method(const vector<vector<double>> &matrix);
vector<vector<double>> product_rotation_matrix(const vector<vector<double>> &matrix1, const vector<vector<double>> &matrix2, int str, int row);
vector<vector<double>> product_matrix(const vector<vector<double>> &matrix1, const vector<vector<double>> &matrix2);

#endif