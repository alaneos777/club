#include <bits/stdc++.h>
using namespace std;

int main(){
	ifstream archivo;
	archivo.open("p067_triangle.txt");
	string linea;
	vector< vector<int> > arr;
	while(getline(archivo, linea)){
		stringstream ss(linea);
		arr.push_back(vector<int>());
		int x;
		while(ss >> x){
			arr.back().push_back(x);
		}
	}
	for(int i = arr.size() - 1; i >= 1; i--){
		for(int j = 0; j < arr[i].size() - 1; j++){
			arr[i - 1][j] += max(arr[i][j], arr[i][j + 1]);
		}
	}
	cout << arr[0][0] << "\n";
	return 0;
}