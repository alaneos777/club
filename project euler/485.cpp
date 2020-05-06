#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<int> divs(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			divs[j]++;
		}
	}
	return divs;
}

const int M = 1e8, sz = 1e5;
const auto divs = sieve(M);

template<typename T>
struct SparseTable{
	vector<vector<T>> ST;
	vector<int> logs;
	int K, N;

	SparseTable(const vector<T> & arr){
		N = arr.size();
		K = log2(N) + 2;
		ST.assign(K + 1, vector<T>(N));
		logs.assign(N + 1, 0);
		for(int i = 2; i <= N; ++i)
			logs[i] = logs[i >> 1] + 1;
		for(int i = 0; i < N; ++i)
			ST[0][i] = arr[i];
		for(int j = 1; j <= K; ++j)
			for(int i = 0; i + (1 << j) <= N; ++i)
				ST[j][i] = max(ST[j - 1][i], ST[j - 1][i + (1 << (j - 1))]);
	}

	T query(int l, int r){
		int j = logs[r - l + 1];
		return max(ST[j][l], ST[j][r - (1 << j) + 1]);
	}
};

int main(){
	SparseTable<int> st(divs);
	lli sum = 0;
	for(int i = 1; i <= M+1-sz; ++i){
		int mx = st.query(i, i+sz-1);
		sum += mx;
	}
	cout << sum << "\n";
	return 0;
}