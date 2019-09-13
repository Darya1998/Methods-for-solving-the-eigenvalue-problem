#include "calculation_partial_choice.h"

vector<vector<double>>  calculation_partial_choice(vector<vector<double>> matrix){
for (int i = 0; i < matrix.size() - 1; i++ ){
    
    for (int j = 1 + i; j < matrix.size(); j ++){
        vector<double> temp_vector;
        
        //ПЕРЕСТАНОВКА СТРОК(ЧАСТИЧНЫЙ ВЫБОР ГЛАВНОГО ЭЛЕМЕНТА)
        if (fabs(matrix[j][i]) > fabs(matrix[i][i])){
            for (int k = 0; k < matrix[0].size(); k++){
                temp_vector.push_back(matrix[j][k]);
            }

            for (int n = 0; n < matrix[0].size(); n++){
                matrix[j][n] = matrix[i][n];
                matrix[i][n] = temp_vector[n];
            }
        }
    }

    // ПРИВЕДЕНИЕ МАТРИЦЫ К ВЕРХНЕТРЕУГОЛЬНОМУ ВИДУ
    for (int j = 1 + i; j < matrix.size(); j ++){
        double temp = matrix[j][i];
        for (int m = 0; m < matrix[0].size(); m++){
            matrix[j][m] += - matrix[i][m] * temp/ matrix[i][i];
            
            if ((fabs(matrix[j][m]) < EPSILON) && (j != m)){
                matrix[j][m] = 0;
            }
        }

    }

}
    return matrix;
};

