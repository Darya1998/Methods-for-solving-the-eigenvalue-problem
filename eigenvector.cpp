#include "eigenvector.h"


double norm(vector<double> sol){
	double norm_evklid;
	for(int i = 0; i < sol.size(); i ++){
		norm_evklid += pow(sol[i],2);
	}
	norm_evklid = pow(norm_evklid, 0.5);
	return norm_evklid;
}

double norm_delta(vector<double> sol1, vector<double> sol2){
	double scalar = 0;
	for (int i = 0; i < sol1.size(); i++){
		// cout << endl << sol1[i] * sol2[i] << endl;
		scalar += (sol1[i] * sol2[i]);
		// cout << "sum = " << scalar << endl;
	}

	return fabs(scalar);
}

vector<double> product(const vector<double> &vec, const vector<vector<double>> &matrix){
    vector<double> vec_new(vec.size());
    for (int i = 0; i < vec.size(); i++){
    	for (int j = 0; j < vec.size(); j++){
    		vec_new[i] += vec[j] * matrix[i][j];
    	}
    }

    return vec_new;
}

vector<vector<double>> find_eigenvector(vector<vector<double>> &matrix, vector<double> &eigenvalues){
	vector<vector<double>> temp_matrix(matrix.size(),vector<double>(matrix.size() + 1));
	vector<vector<double>> matrix_eigenvector(matrix.size(), vector<double>(matrix.size()));

	vector<double> x_solution(matrix.size());//нормированное решение
	vector<double> y_solution;//ненормированное решение

	for (int k = 0; k < eigenvalues.size(); k++){
		for (int i = 0; i < matrix.size(); i++){
			for (int j = 0; j < matrix.size(); j++){
				temp_matrix[i][j] = matrix[i][j];
			}
			temp_matrix[i][matrix.size()] = 0;//вектор правой части
		}

		for (int i = 0; i < matrix.size(); i ++){
			temp_matrix[i][i] -= eigenvalues[k];
		}

		//Вектор правой части/Начальное приближение
		for (int i = 0; i < temp_matrix.size(); i++){
			x_solution[i] = 0;
		}
		x_solution[0] = 1;
		temp_matrix[0][matrix.size()] = 1;

		cout << "Матрица A - lambda * E" << endl;
	    for (const auto &v : temp_matrix){
	        for (const auto &n: v){
	            std::cout << left << setw(15) << setprecision(6) << fixed << n << "\t";
	        }
	        std::cout << std::endl;
	    }
	    std::cout << std::endl;

		double norm_delta_x = 3;
		vector<double> previous_sol(temp_matrix.size());
		vector<vector<double>> up_triangle_matrix = qr_method(temp_matrix).R;
		vector<vector<double>> matr_rotation = qr_method(temp_matrix).T;

		cout << "UP TRIANGLE MATRIX" << endl;
	    for (const auto &v : up_triangle_matrix){
	        for (const auto &n: v){
	            std::cout << left << setw(15) << setprecision(9) << fixed << n << "\t";
	        }
	        std::cout << std::endl;
	    }
	    std::cout << std::endl;

	    int r = 0;
		while(fabs(norm_delta_x - 1) >= EPSILON){
			r++;
			for (int i = 0; i < x_solution.size(); i++){
				previous_sol[i] = x_solution[i];
			}

			vector<double> y_solution = find_solution(up_triangle_matrix);
			// cout << "Y_SOLUTION" << endl;
			// for (const auto n : y_solution){
			// 	cout << n << "   ";
			// }
			// cout << endl;

			//нормируем решение
			// cout << "NORM Y SOLUTION  =  " << norm(y_solution) << endl;
			for (int i = 0; i < y_solution.size(); i++){
				x_solution[i] = y_solution[i]/norm(y_solution);
			}

			
			// cout << "X_SOLUTION" << endl;
			// for (const auto n : x_solution){
			// 	cout << n << "   ";
			// }
			// cout << endl;

			norm_delta_x = norm_delta(previous_sol,x_solution);


			//Повернем вектор правой части
			//x_solution = product(x_solution, matr_rotation);
			for (int i = 0; i < y_solution.size(); i++){
				up_triangle_matrix[i][matrix.size()] = x_solution[i];
			}
			// for (int i = 0; i < y_solution.size(); i++){
			// 	temp_matrix[i][matrix.size()] = x_solution[i];
			// }
			// up_triangle_matrix = qr_method(temp_matrix).R;


			// cout << "X_SOLUTION_NEW" << endl;
			// for (const auto n : x_solution){
			// 	cout << n << "   ";
			// }
			// cout << endl;

			// cout << "PREVIOUS_SOLUTION" << endl;
			// for (const auto n : previous_sol){
			// 	cout << n << "   ";
			// }

			// cout << endl;

			norm_delta_x = norm_delta(previous_sol,x_solution);

			// cout << "NORM DELTA X  =  " << left << setw(15) << setprecision(9) << fixed << fabs(norm_delta_x - 1) << endl;
			// if (r == 20){break;};
		}

		
		for (int i = 0; i < matrix_eigenvector.size(); i ++){
			matrix_eigenvector[k][i] = x_solution[i];
		}


		cout << "Собственный вектор, найден за  " << r <<"  итераций" << endl;
	    for (const auto &v : x_solution){
	        std::cout << left << setw(15) << setprecision(6) << fixed << v << "\t";
	    }

	    std::cout << std::endl;
	}
	return matrix_eigenvector;
}	























		
// 		while(norm_delta_x >= EPSILON){
// 			for (int i = 0; i < x_solution.size(); i++){
// 				previous_sol[i] = x_solution[i];
// 			}

// 			vector<vector<double>> convinient = calculation_partial_choice(temp_matrix);

// 			// cout << "Convinient" << endl;
// 		 //    for (const auto &v : convinient){
// 		 //        for (const auto &n: v){
// 		 //            std::cout << left << setw(15) << setprecision(6) << fixed << n << "\t";
// 		 //        }
// 		 //        std::cout << std::endl;
// 		 //    }
// 		 //    std::cout << std::endl;

// 			y_solution = find_solution(convinient);

// 			//нормируем решение
// 			for (int i = 0; i < y_solution.size(); i++){
// 				x_solution[i] = y_solution[i]/norm(y_solution);
// 				temp_matrix[i][matrix.size()] = x_solution[i];
// 			}

// 			norm_delta_x = norm_delta(previous_sol,x_solution);
// 			// cout << "NORM DELTA X  =  " << norm_delta_x << endl;
	
// 		}

// 		cout << "Собственный вектор" << endl;
//         for (const auto &v : x_solution){
//         	std::cout << left << setw(15) << setprecision(6) << fixed << v << "\t";
//     	}
//     	std::cout << std::endl;

// 	}	

// }





























// void find_eigenvector(vector<vector<double>> &matrix, vector<double> &eigenvalues){
// 	vector<vector<double>> temp_matrix(matrix.size(),vector<double>(matrix.size()));

// 	vector<double> x_solution(matrix.size());//нормированное решение
// 	vector<double> y_solution;//ненормированное решение

// 	for (int k = 0; k < eigenvalues.size(); k++){
// 		for (int i = 0; i < matrix.size(); i++){
// 			for (int j = 0; j < matrix.size(); j++){
// 				temp_matrix[i][j] = matrix[i][j];
// 			}
// 		}

// 		for (int i = 0; i < matrix.size(); i ++){
// 			temp_matrix[i][i] -= eigenvalues[k];
// 		}

// 		//Вектор правой части/Начальное приближение
// 		for (int i = 0; i < temp_matrix.size(); i++){
// 			x_solution[i] = 1;
// 		}

// 		double normJacoby_matrix = 1;
// 		double norm_delta_x = 1;
// 		vector<double> previous_sol(temp_matrix.size());

// 		vector<vector<double>> convinient_matrix = convinient_matrix_jacoby(temp_matrix, x_solution, normJacoby_matrix);
// 		while(norm_delta_x >= EPSILON){
// 			for (int i = 0; i < x_solution.size(); i++){
// 				previous_sol[i] = x_solution[i];
// 			}

// 			vector<double> y_solution = zeydel_relax_solution(1, convinient_matrix, x_solution, normJacoby_matrix);
// 			//нормируем решение
// 			for (int i = 0; i < y_solution.size(); i++){
// 				x_solution[i] = y_solution[i]/norm(y_solution);
// 			}
// 			norm_delta_x = (previous_sol,x_solution);

// 		}

// 		cout << "Собственный вектор" << endl;
// 	    for (const auto &v : x_solution){
// 	        for (const auto &n: v){
// 	            std::cout << left << setw(15) << setprecision(6) << fixed << n << "\t";
// 	        }
// 	        std::cout << std::endl;
// 	    }
// 	    std::cout << std::endl;

// 	}	

// }