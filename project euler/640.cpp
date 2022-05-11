#include <bits/stdc++.h>
using namespace std;

const int N = 6;
const int steps = 5000;

int main(){
	vector<vector<double>> v(2, vector<double>(1<<(2*N)));
	for(int iter = 1; iter <= steps; ++iter){
		for(int m = 0; m < (1 << (2*N)) - 1; ++m){
			v[iter&1][m] = 1;
			for(int x = 1; x <= N; ++x){
				for(int y = 1; y <= N; ++y){
					v[iter&1][m] += min(min(v[(iter-1)&1][m^(1<<(x-1))], v[(iter-1)&1][m^(1<<(y-1))]), v[(iter-1)&1][m^(1<<x+y-1)]) / (N*N);
				}
			}
		}
	}
	cout << fixed << setprecision(6) << v[steps&1][0] << "\n";
	return 0;
}