#include "includes.h"

int main(){
	vector<vector<double>> m (3, vector<double>(3));
	for (int i = 0; i < m.size(); i ++){
		for (int j = 0; j < m.size(); j ++){
			m[i][j] = 1;
		}
	}

	for (const auto &v:m){
		for (const auto &n:v){
			cout << n << "   ";
		}
		cout << endl;
	}

	for (int i = 0 ; i < m.size(); i ++){
		m[i].resize(2);
	}
	m.resize(2);
		for (const auto &v:m){
		for (const auto &n:v){
			cout << n << "   ";
		}
		cout << endl;
	}


	return 0;
}