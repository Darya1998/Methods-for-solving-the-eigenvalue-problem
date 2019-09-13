#include "zeydel_relaxation.h"
//#include "convinient_system.h"
// #include "jacoby.h"
// #include "iter_solution.h"

//НОРМА КУБИЧЕСКАЯ ВЕРХНЕТРЕУГОЛЬНОЙ МАТРИЦЫ
double norm_up_triangle(vector<vector<double>> &matrix){
    double max_row = 0;
     
    for (int i = 0; i < matrix.size(); i++){
        double temp_max_row = 0;
        for (int j = 1 + i; j < matrix.size(); j ++){
            temp_max_row += fabs(matrix[i][j]);
        }

        if (temp_max_row > max_row){
            max_row = temp_max_row;
        }
    }
    return max_row;

}

//ФУНКЦИЯ НАХОЖДЕНИЯ РЕШЕНИЯ(МЕТОД ЗЕЙДЕЛЯ, РЕЛАКСАЦИИ)
vector<double> zeydel_relax_solution(double &parametr, vector<vector<double>> &matrix_zeydel, vector<double> &changed_vector_zeydel, double norm_B){

    // cout << "Норма матрицы, приведенной к удобному виду" << norm_B << endl;

	//НОРМА ВЕРХНЕТРЕУГОЛЬНОЙ МАТРИЦЫ
	double norm_B2 = norm_up_triangle(matrix_zeydel);

	//НОВОЕ ЗНАЧЕНИЕ ЭПСИОЛОН
    
	double EPS2 = (1 - norm_B)/(norm_B2)* EPSILON;

    
	//ВЫЛЕЛЯЕМ ПАМЯТЬ ПОД ВЕКТОРА РЕШЕНИЙ(ТЕКУЩИЙ И ПРЕДЫДУЩИЙ)
	vector<double> init_solution(matrix_zeydel.size());
    vector<double> new_solution(matrix_zeydel.size());


    //ПУСТЬ НАЧАЛЬНЫМ ПРИБЛЕЖНИЕМ БУДЕТ НУЛЕВОЙ ВЕКТОР
    for (int i = 0; i < matrix_zeydel.size(); i ++){
        init_solution[i] = 0;
        new_solution[i] = 0;
    }
    
    //РАЗНОСТЬ X^N И X^(N-1) РЕШЕНИЙ
    std::vector<double> vector_difference(matrix_zeydel.size());

    //НОРМА РАЗНОСТИ X^N И X^(N-1) РЕШЕНИЙ
    double norm_difference = 1;

    while(norm_difference >= EPS2){

        //ОБНУЛЯЕМ НОВЫЙ ВЕКТОР РЕШЕНИЙ
        for (int i = 0; i < matrix_zeydel.size(); i ++){
            init_solution[i] = new_solution[i];
            new_solution[i] = 0;
        }

        for (int i = 0; i < matrix_zeydel.size(); i ++){
        	for (int j = 0; j < matrix_zeydel.size(); j ++){
        		//ПОДСЧЕТ УМНОЖЕНИЯ НИЖНЕТРЕУГОЛЬНОЙ МАТРИЦЫ НА ИЗМЕНЕННЫЙ ВЕКТОР
        		double product_B1_xnew = 0;
        		for (int k = 0; k < i; k ++){
        			product_B1_xnew += matrix_zeydel[i][k] * new_solution[k];
        		}
        		

        		//ПОДСЧЕТ УМНОЖЕНИЯ ВЕРХНЕТРЕУГОЛЬНОЙ МАТРИЦЫ НА ПЕРВОНАЧАЛЬНЫЙ ВЕКТОР
        		double product_B2_xold = 0;
        		for (int k = 1 + i; k < matrix_zeydel.size(); k++){
        			product_B2_xold += matrix_zeydel[i][k] * init_solution[k];
        		}

        		new_solution[i] = (1 - parametr) * init_solution[i] + parametr * product_B1_xnew + parametr * product_B2_xold + parametr * changed_vector_zeydel[i];
        	}

        }

    }

    cout << "Количество итераций  = " << i << endl;

    return new_solution;
}

