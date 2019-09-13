#include "hesenberg.h"

vector<vector<double>> matrix_hesenbegr(const vector<vector<double>> matrix){
    double c, s;
    vector<vector<double>> matrix_new(matrix.size(), vector<double>(matrix.size()));
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix.size(); j++){
            matrix_new[i][j] = matrix[i][j];
        }
    }

    for (int i = 1; i < matrix_new[0].size() - 1; i++){
        for(int j = 1 + i; j < matrix_new.size(); j++){
            if (fabs(matrix_new[i][i-1]) + fabs(matrix_new[j][i-1]) != 0){
                c = matrix_new[i][i-1]/sqrt(sqr(matrix_new[i][i-1])+ sqr(matrix_new[j][i-1]));
                s = matrix_new[j][i-1]/sqrt(sqr(matrix_new[i][i-1])+ sqr(matrix_new[j][i-1])); 
                // cout << "Alpha = " << c << endl;
                // cout << "Beta = " << s << endl;
                
                //Находим матрицу R
                for (int m = i - 1; m < matrix_new[i].size(); m++){ ;
                    double temp = matrix_new[i][m];
                    matrix_new[i][m] = c * temp + s * matrix_new[j][m];
                    matrix_new[j][m] = -s * temp + c * matrix_new[j][m];

                }

                for (int m = 0; m < matrix_new[i].size(); m++){//Домножаем на транспонированную
                    double temp = matrix_new[m][i];
                    matrix_new[m][i] = c * temp + s * matrix_new[m][j];
                    matrix_new[m][j] = -s * temp + c * matrix_new[m][j];

                }

                cout << "Приближение" << endl;
                for (const auto &v : matrix_new){
                    for (const auto &n: v){
                        std::cout << left << setw(15) << setprecision(6) << fixed << n << "\t";
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl;



                //СОЗДАНИЕ НОВОЙ МАТРИЦЫ 
                vector<vector<double>> MatrixNew(matrix.size(), vector<double>(matrix[0].size()));
                for (int i = 0; i < matrix.size(); i++){
                    for (int j = 0; j < matrix[0].size(); j++){
                        if (j == i){
                            MatrixNew[i][j] = 1;
                        }
                        else MatrixNew[i][j] = 0;
                    }
                }

                MatrixNew[i][i] = c;
                MatrixNew[j][j] = c;
                MatrixNew[i][j] = s;
                MatrixNew[j][i] = -s;

            }
        }
           
    }

    cout << "Матрица Хессенберга" << endl;
    for (const auto &v : matrix_new){
        for (const auto &n: v){
            std::cout << left << setw(15) << setprecision(6) << fixed << n << "\t";
        }
    std::cout << std::endl;
    }
    std::cout << std::endl;
    return matrix_new;
}    