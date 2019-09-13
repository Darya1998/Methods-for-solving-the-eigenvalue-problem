#include "includes.h"
#include "function_read_matrix.h"
#include "qr.h"
#include "get_matrix_r.h"
#include "hesenberg.h"
#include "shift.h"
#include "calculation_partial_choice.h"
#include "find_solution.h"
#include "eigenvector.h"
#include "reyel.h"

int main() {
	vector<vector<double>> matrix = open_test_read_slae("/home/darya/Method_of_calculation/LabaFourth/_Lab4/EUGEN/EIGENS.txt");
	
	vector<double> eigenvalues(matrix.size());//вектор собственных значений

	QR_Matrix M;
	vector<vector<double>> result_matrix = matrix_r(matrix, eigenvalues);
	
	cout << "--------------------------------------------------------------" << endl;

	//Найдем собственные вектора
	vector<vector<double>> matrix_eigen = find_eigenvector(matrix, eigenvalues);

	

	// result_matrix = matrix_r(new_matrix_hesenberg, eigenvalues);

	// cout << "QR со сдвигом"<< endl;
	
	// vector<double> vec = shift_matrix(matrix);

	// cout << "QR со сдвигом и с матрицей Хессенберга"<< endl;
	// vector<vector<double>>  new_matrix_hesenberg = matrix_hesenbegr(matrix);
	
	// cout << endl;
	// cout << "Матрица Хессенберга" << endl;
 //    for (const auto &v : new_matrix_hesenberg){
 //        for (const auto &n: v){
 //            std::cout << left << setw(15) << setprecision(6) << fixed << n << "\t";
 //        }
 //        std::cout << std::endl;
 //    }
 //    std::cout << std::endl;
	// vector<double>vec1 = shift_matrix(new_matrix_hesenberg);

	// reyel_eigen_value(matrix);


	return 0;
}