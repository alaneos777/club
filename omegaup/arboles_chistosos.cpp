#include <bits/stdc++.h>

using namespace std;

typedef int lli;

template<typename T>
struct FenwickTree{
	int N;
	vector<T> bit;

	FenwickTree(int N){
		this->N = N;
		bit.assign(N, 0);
	}

	void update(int pos, T value){
		while(pos < N){
			bit[pos] += value;
			pos |= pos + 1;
		}
	}

	T query(int r){
		T res = 0;
		while(r >= 0){
			res += bit[r];
			r = (r & (r + 1)) - 1;
		}
		return res;
	}

	T query(int l, int r){
		return query(r) - query(l - 1);
	}
};

struct info{
	int start, end, parity;
	lli value;
};

int contador;

void dfs(vector<info> & A, vector< vector<int> > & nodos, int pos, int ant, int nivel){
	A[pos].parity = nivel;
	A[pos].start = ++contador;
	for(int & v : nodos[pos])
		if(v != ant)
			dfs(A, nodos, v, pos, (nivel + 1) & 1);
	A[pos].end = contador;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	contador = -1;
	int n, m;
	int u, v;
	int t, x;
	lli val;
	cin >> n >> m;
	vector<info> A(n);
	for(int i = 0; i < n; ++i){
		cin >> A[i].value;
	}
	vector< vector<int> > nodos(n, vector<int>());
	for(int i = 0; i < (n - 1); ++i){
		cin >> u >> v;
		nodos[u - 1].push_back(v - 1);
		nodos[v - 1].push_back(u - 1);
	}
	dfs(A, nodos, 0, -1, 0);
	vector<FenwickTree<lli>> ST(2, FenwickTree<lli>(n));
	for(int i = 0; i < m; ++i){
		cin >> t >> x;
		--x;
		if(t == 1){
			cin >> val;
			ST[A[x].parity].update(A[x].start, val);
			ST[A[x].parity].update(A[x].end + 1, -val);
		}else if(t == 2){
			cout << (A[x].value + ST[A[x].parity].query(0, A[x].start) - ST[1 - A[x].parity].query(0, A[x].start)) << "\n";
		}
	}
	return 0;
}