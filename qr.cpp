#include "qr.h"
vector<vector<double>> product_rotation_matrix(const vector<vector<double>> &matrix1, const vector<vector<double>> &matrix2, int str, int row){
    vector<vector<double>> product_rotation_matrix(matrix2.size(), vector<double>(matrix2[0]. size()));
    for (int i = 0; i < matrix2.size(); i++){
        for (int j = 0; j < matrix2[0].size(); j++){
            product_rotation_matrix[i][j] = matrix2[i][j];
        }
    }
    for (int k = 0; k < matrix2[0]. size(); k ++){
        product_rotation_matrix[str][k] = matrix2[str][k] * matrix1[str][str] + matrix2[row][k] * matrix1[str][row];
        product_rotation_matrix[row][k] = matrix2[row][k] * matrix1[str][str] - matrix2[str][k] * matrix1[str][row];
    }

    return product_rotation_matrix;
}

//Перемножение матриц R(вернхнетреугольная) на T(транспонированная)
vector<vector<double>> product_matrix(const vector<vector<double>> &matrix1, const vector<vector<double>> &matrix2){
    int new_row = matrix2.size();
    int new_col = matrix2[0].size();
    vector<vector<double>> matrix_product(new_row, vector<double>(new_col));
    for (int i = 0; i < new_row; i++){
        for (int j = 0; j < new_col; j++){
            matrix_product[i][j] = 0;
            for (int k = 0; k < new_col; k++){
                matrix_product[i][j] = matrix_product[i][j] + (matrix1[i][k]*matrix2[k][j]);
            }
        }

    }
    return matrix_product;
}

QR_Matrix qr_method(const vector<vector<double>> &matrix){
    double c, s;
    QR_Matrix struct_Matrix;
    struct_Matrix.T = vector<vector<double>>(matrix.size(),vector<double>(matrix.size()));
    struct_Matrix.R = vector<vector<double>>(matrix.size(),vector<double>(matrix[0].size()));
    struct_Matrix.RQ = vector<vector<double>>(matrix.size(),vector<double>(matrix.size()));


    vector<vector<double>> matr_r_new(matrix.size(), vector<double>(matrix[0].size()));
    //Запишем в нее данные исходной матрицы
    for (int i = 0; i < matrix.size(); i ++){
        for (int j = 0; j < matrix[0].size(); j ++){
            matr_r_new[i][j] = matrix[i][j];
        }
    }
    // СОЗДАНИЕ ЕДИНИЧНОЙ МАТРИЦЫ (КВАДРАТНАЯ)
    vector<vector<double>> MatrixInitial(matrix.size(), vector<double>(matrix.size()));
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix.size(); j++){
            if (i == j){
                MatrixInitial[i][j] = 1;
            }
            else{
                MatrixInitial[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < matr_r_new[0].size() - 1; i++){
        for(int j = 1 + i; j < matr_r_new.size(); j++){
            if (fabs(matr_r_new[i][i]) + fabs(matr_r_new[j][i]) != 0){
                c = matr_r_new[i][i]/sqrt(sqr(matr_r_new[i][i])+ sqr(matr_r_new[j][i]));
                s = matr_r_new[j][i]/sqrt(sqr(matr_r_new[i][i])+ sqr(matr_r_new[j][i])); 
                //Находим матрицу R
                for (int m = i; m < matr_r_new[i].size(); m++){ ;
                    double temp = matr_r_new[i][m];
                    matr_r_new[i][m] = c * temp + s * matr_r_new[j][m];
                    matr_r_new[j][m] = -s * temp + c * matr_r_new[j][m];
                }

                //СОЗДАНИЕ НОВОЙ МАТРИЦЫ 
                vector<vector<double>> MatrixNew(matr_r_new.size(), vector<double>(matr_r_new[0].size()));
                for (int i = 0; i < matr_r_new.size(); i++){
                    for (int j = 0; j < matr_r_new[0].size(); j++){
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

            //ПЕРЕМНОЖЕНИЕ МАТРИЦ ПОВОРОТА
            MatrixInitial = product_rotation_matrix(MatrixNew, MatrixInitial, i , j); //Полиучим матрицу T
            }
        }
           
    }

    //транспонированная матрица к матрице Т => получис матрицу Q
    vector<vector<double>> transpose_matrix(MatrixInitial.size(),vector<double>(MatrixInitial.size()));
    for(int i = 0; i < MatrixInitial.size(); i++){
        for (int j = 0; j < MatrixInitial.size(); j++){
            transpose_matrix[i][j] = MatrixInitial[j][i];

        }
    }
        
    //Умножим R = TA на T(транспонированную) = RQ
    vector<vector<double>> matrix_new;
    matrix_new = product_matrix(matr_r_new, transpose_matrix);

    for(int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[0].size(); j++){
            struct_Matrix.R[i][j] = matr_r_new[i][j];
        }
    }


    for(int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix.size(); j++){
            struct_Matrix.T[i][j] = MatrixInitial[i][j];
        }
    }


    for(int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix.size(); j++){
            struct_Matrix.RQ[i][j] = matrix_new[i][j];
        }
    }

    return struct_Matrix;
}

