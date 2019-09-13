#include "get_matrix_r.h" 
#include "qr.h"

vector<vector<double>> matrix_r(const vector<vector<double>> &matrix, vector<double> &eigenvalues){
	//k-ое приближение
	vector<vector<double>> temp_matrix(matrix.size(),vector<double>(matrix.size()));
	for (int i = 0; i < matrix.size(); i++){
		for (int j = 0; j < matrix[0].size(); j ++){
			temp_matrix[i][j] = matrix[i][j];
		}
	}
	//k+1 приближение
	vector<vector<double>> aproximate_matrix(matrix.size(),vector<double>(matrix.size()));
	int i = 0;//счетчик кол-ва приближений
	
	// double sum = 1;
	// for (int i = 0; i < matrix.size(); i++){
	// 	for (int j = 0; j < matrix[0].size(); j ++){
	// 		aproximate_matrix[i][j] = temp_matrix[i][j];
	// 	}
	// }

	// while(sum >= EPSILON){
	// 	aproximate_matrix = qr_method(aproximate_matrix).RQ;
	// 	sum = 0;
	// 	for (int i = 0; i < aproximate_matrix.size(); i++){
	// 		for (int j = 0; j < i; j++){
	// 			sum += fabs(aproximate_matrix[i][j]);
	// 		}
	// 	}

	// }

	// cout << "Result Matrix" << endl;
	// for (const auto &v:aproximate_matrix){
	// 	for (const auto &n:v){
	// 		cout << n << "   ";
	// 	}
	// 	cout << endl;
	// }

	while(temp_matrix.size()!= 1 ){

		aproximate_matrix = qr_method(temp_matrix).RQ;
		
		// cout << "\n Матрица" << i << "-ого  приближения" << endl;
	    // for (const auto &v : aproximate_matrix){
  //   		for (const auto &n: v){
  //       		std::cout << left << setw(15) << setprecision(6) << fixed << n << "\t";
  //   		}
  //   		std::cout << std::endl;
		// }
		// std::cout << std::endl;

		//Проверка:обнунились ли элементы на нижней строке?(если да, то уменьшаем размерность матрица 
		//и запоминаем собственное число)
		int dimension = aproximate_matrix.size();
		int counters = 0;
		// for (int i = 0; i < dimension - 1; i ++){
		// 	if (fabs(aproximate_matrix[dimension-1][i]) < EPSILON){
		// 		counters++;
		// 	}
		// }

		if (fabs(aproximate_matrix[dimension-1][dimension-2]) < EPSILON){//элемент на нижней строке на побочной диагонали
			counters = 1;
		}

		if (counters == 1){//Если элемент обнунились
			eigenvalues[matrix.size() - dimension] = aproximate_matrix[dimension - 1][dimension - 1];//записываем собственное число
			for (int i = 0 ; i < dimension; i ++){			//уменьшаем размерность матриц
				aproximate_matrix[i].resize(dimension - 1);
				temp_matrix[i].resize(dimension - 1);

			}
			aproximate_matrix.resize(dimension - 1);
			temp_matrix.resize(dimension - 1);

		}

	
		
		for (int i = 0; i < temp_matrix.size(); i++){
			for (int j = 0; j < temp_matrix[0].size(); j ++){
				temp_matrix[i][j] = aproximate_matrix[i][j];
			}
		}
		i++;
	}

	//Записваем последнее собственное число
	eigenvalues[matrix.size() - 1] = temp_matrix[0][0];

	cout << "Метод сошелся за  " << i << "итераций" << endl;
	for (const auto &n:eigenvalues){
		cout << n << "   ";
	}
	cout << endl << endl;
	//return aproximate_matrix;
	return temp_matrix;

}