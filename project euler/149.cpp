#include <bits/stdc++.h>
using namespace std;

int kadane(const vector<int> & a){
	int ans = 0, curr = 0;
	for(int x : a){
		curr = max(0, curr + x);
		ans = max(ans, curr);
	}
	return ans;
}

const int M = 2000;

int main(){
	vector<int> s(M*M+1);
	for(int64_t k = 1; k <= 55; ++k){
		s[k] = (100003 - 200003*k + 300007*k*k*k) % 1000000 - 500000;
	}
	for(int k = 56; k <= M*M; ++k){
		s[k] = (s[k-24] + s[k-55] + 1000000) % 1000000 - 500000;
	}
	vector<vector<int>> mat(M, vector<int>(M));
	for(int i = 0; i < M*M; ++i){
		mat[i/M][i%M] = s[i+1];
	}
	int ans = -2e9;
	for(int i = 0; i < M; ++i){
		vector<int> tmp;
		for(int j = 0; j < M; ++j){
			tmp.push_back(mat[i][j]);
		}
		ans = max(kadane(tmp), ans);
	}
	for(int j = 0; j < M; ++j){
		vector<int> tmp;
		for(int i = 0; i < M; ++i){
			tmp.push_back(mat[i][j]);
		}
		ans = max(kadane(tmp), ans);
	}
	for(int a = 0; a < M; ++a){
		vector<int> tmp;
		for(int b = 0; a+b < M && b < M; ++b){
			tmp.push_back(mat[a+b][b]);
		}
		ans = max(kadane(tmp), ans);
	}
	for(int a = 0; a < M; ++a){
		vector<int> tmp;
		for(int b = 0; b < M && a+b < M; ++b){
			tmp.push_back(mat[b][a+b]);
		}
		ans = max(kadane(tmp), ans);
	}
	for(int a = 0; a < M; ++a){
		vector<int> tmp;
		for(int b = 0; a-b >= 0 && b < M; ++b){
			tmp.push_back(mat[a-b][b]);
		}
		ans = max(kadane(tmp), ans);
	}
	for(int a = 0; a < M; ++a){
		vector<int> tmp;
		for(int b = 0; b < M && a+b < M; ++b){
			tmp.push_back(mat[M-1-b][a+b]);
		}
		ans = max(kadane(tmp), ans);
	}
	cout << ans << "\n";
	return 0;
}