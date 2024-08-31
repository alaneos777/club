#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const ld eps = 1e-12;
bool eq(ld a, ld b){return abs(a-b) < eps;}

int gauss(vector<vector<ld>> & A){
	int m = A.size(), n = A[0].size(), i = 0, j = 0;
	while(i < m && j < n){
		if(eq(A[i][j], 0)){
			for(int k = i + 1; k < m; k++){
				if(!eq(A[k][j], 0)){
					swap(A[i], A[k]);
					break;
				}
			}
		}
		if(!eq(A[i][j], 0)){
			ld inv_mult = 1.0l / A[i][j];
			if(!eq(A[i][j], 1)){
				for(int l = 0; l < n; ++l){
					A[i][l] = A[i][l] * inv_mult;
				}
			}
			for(int k = 0; k < m; k++){
				if(k != i && !eq(A[k][j], 0)){
					ld inv_adit = -A[k][j];
					for(int l = 0; l < n; ++l){
						A[k][l] += inv_adit * A[i][l];
					}
				}
			}
			i++;
		}
		j++;
	}
	return i;
}

const int N = 100;
const ld pr[] = {1.0l/6.0l, 4.0l/6.0l, 1.0l/6.0l};

int main(){
	vector<vector<ld>> A(N, vector<ld>(N+1));
	A[0][0] = 1;
	for(int d = 1; d < N; ++d){
		A[d][d] = 1;
		for(int i : {-1, 0, 1}){
			for(int j : {-1, 0, 1}){
				ld p = pr[i+1], q = pr[j+1];
				int D = d+i+j;
				if(D >= N) D -= N;
				if(D < 0) D += N;
				A[d][D] -= p*q;
			}
		}
		A[d][N] = 1;
	}
	gauss(A);
	cout << fixed << setprecision(10) << A[N/2][N] << "\n";
	return 0;
}