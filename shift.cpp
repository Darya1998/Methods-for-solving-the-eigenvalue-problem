#include "shift.h"
#include "qr.h"

vector<double> shift_matrix(const vector<vector<double>> &matrix){
	double dim = matrix.size();
	double s;
	int i = 0;//счетчик;

	vector<vector<double>> temp_matrix(dim,vector<double>(dim));
	for (int i = 0; i < dim; i++){
		for (int j = 0; j < dim; j++){
			temp_matrix[i][j] = matrix[i][j];

		}
	}

	vector<double> eigenvalues(matrix.size());//вектор собственных значений
	vector<vector<double>> aproximate_matrix;

	while(temp_matrix.size()!= 1 ){
		dim = temp_matrix.size();
		s = temp_matrix[dim-1][dim-1];//выбрали величину сдвига
		for (int i = 0; i < dim; i ++){
			temp_matrix[i][i] -= s;//сдвинули
		}
		
		
		// for (const auto &v:temp_matrix){
		// 	for (const auto &n:v){
		// 		cout << n << "  ";
		// 	}
		// 	cout << endl;
		// }
		// cout << endl;
		
		aproximate_matrix = qr_method(temp_matrix).RQ;

		for (int i = 0; i < dim; i ++){
			aproximate_matrix[i][i] += s;
		}
		cout << "B*" << endl;

		for (const auto &v:aproximate_matrix){
			for (const auto &n:v){
				cout << n << "  ";
			}
			cout << endl;
		}
		cout << endl;

		int counters = 0;

		if (fabs(aproximate_matrix[dim-1][dim-2]) < EPSILON){//элемент на нижней строке на побочной диагонали
			counters = 1;
		}

		if (counters == 1){//Если элемент обнунились
			eigenvalues[matrix.size() - dim] = aproximate_matrix[dim - 1][dim - 1];//записываем собственное число
			
			for (int i = 0 ; i < dim; i ++){//уменьшаем размерность матриц
				aproximate_matrix[i].resize(dim - 1);
				temp_matrix[i].resize(dim - 1);
			}
			aproximate_matrix.resize(dim - 1);
			temp_matrix.resize(dim - 1);

		}
		
		for (int i = 0; i < temp_matrix.size(); i++){
			for (int j = 0; j < temp_matrix[0].size(); j ++){
				temp_matrix[i][j] = aproximate_matrix[i][j];
			}
		}
		// cout << i + 1<< "-ая итерация/ " << "используем сдвиг" << endl;
		// for (const auto &v:temp_matrix){
		// 	for (const auto &n:v){
		// 		cout << n << "  ";
		// 	}
		// 	cout << endl;
		// }
		// cout << endl;

		i++;
	}

	cout << "Метод сошелся за  " << i << "  итераций" << endl;

	//Записваем последнее собственное число
	eigenvalues[matrix.size() - 1] = temp_matrix[0][0];
	for(const auto n:eigenvalues){
		cout << n << "   ";
	}
	cout << endl;

	return eigenvalues;

}