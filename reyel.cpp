#include "reyel.h"

// double reyel_eigen_value(const vector<vector<double>> &matrix, const vector<vector<double>> &matrix_eigen){
// 	vector<double> start1_vector(matrix.size());
// 	double start1_number;

// 	for (int k = 0; k < matrix.size(); k ++){
// 		start1_number = 0;
// 		//Начальное приближение
// 		for (int i = 0; i < matrix_eigen.size(); i ++){
// 			start1_vector[i] = matrix_eigen[k][i];
// 		}
// 		vector<double> start1_product = product(start1_vector, matrix);
		
// 		for (int i = 0; i < start1_product.size(); i ++){
// 			start1_number += start1_product[i] * start1_vector[i];
// 		}
// 		cout << "СОБСТВЕННОЕ ЧИСЛО =  "<< start1_number << endl;
// 	}



// 	return start1_number;

// }

void reyel_eigen_value(const vector<vector<double>> &matrix){
	vector<double> start1_vector(matrix.size());
	vector<vector<double>> temp_matrix(matrix.size(),vector<double>(matrix.size() + 1));


	vector<vector<double>> start_matrix(matrix.size(), vector<double>(matrix.size()));//Начальные приближения
	// for (int i = 0; i < start_matrix.size(); i ++){
	// 	for (int j = 0; j < start_matrix.size(); j++){
	// 		start_matrix[i][j] = 1;
	// 		if(i == j){
	// 			start_matrix[i][i] = 0;
	// 		}

	// 	}
		
	// }

	// start_matrix = {{-0.70,0.3,-0.23,-0.42},{0.1,0.68,-0.59,0.38}, {0.45,-0.02,-0.40,-0.73},{0.2,0.68,0.57,-0.38}};
	start_matrix = {{0.864461,0.003389,0.2445953,0.439169},{-0.011907,0.709759,-0.607555,0.356337}, {0.502548,0.015796,-0.430896,-0.749349},{-0.003432,0.704259,0.620789,-0.344426}};

	double start1_number;
	vector<double> x_solution(matrix.size());//нормированное решение
	vector<double> y_solution;//ненормированное решение

	for (int k = 0; k < start_matrix.size(); k++){
		for (int i = 0; i < start_matrix.size(); i++){
			start1_vector[i] = start_matrix[k][i];
		}
		cout << "Начальное приближение ";
		for (const auto &n:start1_vector){cout << n << "  ";}
		cout << endl;

		double norm_delta_x = 2;
		while(fabs(norm_delta_x -1) >= EPSILON){

			start1_number = 0;

			vector<double> start1_product = product(start1_vector, matrix);
			for (int i = 0; i < start1_product.size(); i ++){
				start1_number += start1_product[i] * start1_vector[i];//получили собственное число
			}

			//A - lambda * E
			for (int i = 0; i < matrix.size(); i++){
				for (int j = 0; j < matrix.size(); j++){
					temp_matrix[i][j] = matrix[i][j];
				}
				temp_matrix[i][matrix.size()] = start1_vector[i];//вектор правой части
			}

			for (int i = 0; i < matrix.size(); i ++){
				temp_matrix[i][i] -= start1_number;
			}

			//Решим систему методом Гаусса
			vector<vector<double>> triangle_matrix = calculation_partial_choice(temp_matrix);
			y_solution = find_solution(triangle_matrix);

			//нормируем решение
			// cout << "NORM Y SOLUTION  =  " << norm(y_solution) << endl;
			for (int i = 0; i < y_solution.size(); i++){
				x_solution[i] = y_solution[i]/norm(y_solution);
			}

			norm_delta_x = fabs(norm_delta(start1_vector,x_solution));
			cout << endl;
			cout << "Собственный вектор/Найденное приближение" << endl;
		    for (const auto &v : start1_vector){
		        std::cout << left << setw(15) << setprecision(6) << fixed << v << "\t";
		    }
		    std::cout << std::endl;

		    cout << "Собственный вектор(предыдущий)/Найденное приближение" << endl;
		    for (const auto &v : x_solution){
		        std::cout << left << setw(15) << setprecision(6) << fixed << v << "\t";
		    }
		    std::cout << std::endl;


			cout << "Скалярное произведение минус 1 =  " << left << setw(15) << setprecision(12) << fixed << norm_delta_x - 1<< endl;

			for (int i = 0; i < x_solution.size(); i++){//перезаписали вектор правой части
				start1_vector[i] = x_solution[i];
				temp_matrix[i][matrix.size()] = x_solution[i];
			}

		}

		cout << "СОБСТВЕННОЕ ЧИСЛО =  " << start1_number << endl;
		cout <<"СОБСТВЕННЫЙ ВЕКТОР" << endl;
		for (int i = 0; i < x_solution.size(); i ++){
			cout << x_solution[i] << "\t";
		}
		cout << endl;




	}
	
}