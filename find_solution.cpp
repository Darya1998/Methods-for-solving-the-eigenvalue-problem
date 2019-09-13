#include "find_solution.h"

std::vector<double> find_solution(const vector<vector<double>> &matrix){
    vector <double> solution;
 
    solution.resize(matrix.size());
    for (int i = 0; i < matrix.size(); i++){
        solution[i] = 0;
    }
    double root, combination_roots;
    // for (int i = matrix.size() - 1; i >= 0; i--){
    //     combination_roots = 0;
    //     for (int j = i + 1; j <= matrix.size(); j --){
    //         combination_roots += matrix[i][j] * solution[j];
    //     }
    //     root = (matrix[i][matrix[0].size() - 1] - combination_roots)/matrix[i][i];
    //     cout << root << endl;
    //     solution[i] = root;
    // }

    int N = matrix.size();
    solution[N-1] = matrix[N-1][N]/matrix[N-1][N-1];
    for (int i=N-2; i>=0; i--)
    {
        solution[i] = matrix[i][N]/matrix[i][i];
        for (int j=i+1;j<N;j++) solution[i]-=matrix[i][j]*solution[j]/matrix[i][i];
    }

    return solution;
}