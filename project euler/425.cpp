#include <bits/stdc++.h>
using namespace std;

struct disjointSet{
	int N;
	vector<short int> rank;
	vector<int> parent;

	disjointSet(int N): N(N), parent(N), rank(N){}

	void makeSet(int v){
		parent[v] = v;
	}

	int findSet(int v){
		if(v == parent[v]) return v;
		return parent[v] = findSet(parent[v]);
	}

	void unionSet(int a, int b){
		a = findSet(a), b = findSet(b);
		if(a == b) return;
		if(rank[a] < rank[b]){
			parent[a] = b;
		}else{
			parent[b] = a;
			if(rank[a] == rank[b]) ++rank[a];
		}
	}
};

vector<int> primes;
vector<bool> is;
void sieve(int n){
	is.resize(n+1, true);
	is[0] = is[1] = false;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
}

const int M = 1e7;

int main(){
	sieve(M);
	vector<int> ten(10, 1);
	for(int i = 1; i < 10; ++i){
		ten[i] = ten[i-1] * 10;
	}
	disjointSet ds(M+1);
	for(int i = 0; i <= M; ++i){
		ds.makeSet(i);
	}
	vector<vector<pair<int, int>>> edges(M+1);
	for(int i : primes){
		string str = to_string(i);
		int digits = str.size();
		int tmp = i;
		for(int j = 0; j < digits; ++j){
			int digit = tmp % 10;
			tmp /= 10;
			for(int d = 0; d <= 9; ++d){
				if(d == 0 && j == digits-1) continue;
				if(d == digit) continue;
				int next = i + ten[j] * (d - digit);
				if(next > M) continue;
				if(!is[next]) continue;
				edges[max(i, next)].emplace_back(i, next);
			}
		}
		for(int d = 1; d <= 9; ++d){
			int next = i + ten[digits] * d;
			if(next > M) continue;
			if(!is[next]) continue;
			edges[max(i, next)].emplace_back(i, next);
		}
	}
	
	int64_t ans = 0;
	for(int p : primes){
		for(const auto & edge : edges[p]){
			ds.unionSet(edge.first, edge.second);
		}
		if(ds.findSet(2) != ds.findSet(p)){
			ans += p;
		}
	}
	cout << ans << "\n";
	return 0;
}