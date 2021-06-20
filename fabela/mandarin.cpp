#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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
				ST[j][i] = min(ST[j - 1][i], ST[j - 1][i + (1 << (j - 1))]);
	}

	T mini(int l, int r){
		int j = logs[r - l + 1];
		return min(ST[j][l], ST[j][r - (1 << j) + 1]);
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int& ai : a){
		cin >> ai;
	}
	SparseTable<int> st(a);
	lli ans = 0;
	for(int i = 0; i < n; ++i){
		for(int j = i; j < n; ++j){
			ans = max(ans, lli(j-i+1) * st.mini(i, j));
		}
	}
	cout << ans << "\n";
	return 0;
}