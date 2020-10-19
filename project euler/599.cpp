#include <bits/stdc++.h>
using namespace std;
using lli = __uint128_t;

struct FenwickTree{
	int N;
	vector<int> bit;

	FenwickTree(int N): N(N){
		bit.resize(N);
	}

	void update(int pos, int value){
		while(pos < N){
			bit[pos] += value;
			pos |= pos + 1;
		}
	}

	int query(int r){
		int res = 0;
		while(r >= 0){
			res += bit[r];
			r = (r & (r + 1)) - 1;
		}
		return res;
	}
};

const int n = 24;
vector<lli> fact(n, 1);

lli encode(const vector<int8_t> & pi){
	lli ans = 1;
	FenwickTree ft(n);
	for(int i = n-1, j = 0; i >= 0; --i, ++j){
		ans += ft.query(pi[i] - 1) * fact[j];
		ft.update(pi[i], 1);
	}
	return ans;
}

vector<int8_t> get_permutation(const vector<vector<int8_t>> & cycles){
	vector<int8_t> pi(n);
	iota(pi.begin(), pi.end(), 0);
	for(const auto & cycle : cycles){
		for(int i = 0; i < cycle.size(); ++i){
			pi[cycle[i]-1] = cycle[(i+1) % cycle.size()]-1;
		}
	}
	return pi;
}

vector<int8_t> comb(const vector<int8_t> & f, const vector<int8_t> & g){
	vector<int8_t> h(n);
	for(int i = 0; i < n; ++i){
		h[i] = g[f[i]];
	}
	return h;
}

int cnt_cycles(const vector<int8_t> & pi){
	vector<bool> vis(n);
	int cycles = 0;
	for(int i = 0; i < n; ++i){
		if(!vis[i]){
			int u = i;
			do{
				vis[u] = true;
				u = pi[u];
			}while(u != i);
			cycles++;
		}
	}
	return cycles;
}

int main(){
	for(lli i = 2; i < n; ++i){
		fact[i] = i * fact[i-1];
	}

	vector<int8_t> id(n);
	iota(id.begin(), id.end(), 0);

	vector<int8_t> R = get_permutation({{13, 14, 16, 15}, {10, 2, 19, 22}, {12, 4, 17, 24}});
	vector<int8_t> L = get_permutation({{5, 6, 8, 7}, {3, 11, 23, 18}, {1, 9, 21, 20}});
	vector<int8_t> U = get_permutation({{1, 2, 4, 3}, {9, 5, 17, 13}, {10, 6, 18, 14}});
	vector<int8_t> D = get_permutation({{21, 22, 24, 23}, {11, 15, 19, 7}, {12, 16, 20, 8}});
	vector<int8_t> F = get_permutation({{9, 10, 12, 11}, {3, 13, 22, 8}, {4, 15, 21, 6}});
	vector<int8_t> B = get_permutation({{17, 18, 20, 19}, {1, 7, 24, 14}, {2, 5, 23, 16}});

	vector<vector<int8_t>> movs = {R, L, U, D, F, B};

	vector<int> P = {0, 0, 19053144, 17404632, 3289734, 19675656, 13976640, 1591128, 6753434, 4262412, 261156, 1076040, 664825, 17640, 87500, 58800, 420, 3528, 3010, 0, 56, 84, 0, 0, 1}; //vector<int>(n+1);

	/*set<lli> vis;
	queue<vector<int8_t>> q;
	P[cnt_cycles(id)]++;
	vis.insert(encode(id));
	q.push(id);
	while(!q.empty()){
		if(vis.size() % 10000 == 0) cout << vis.size() << "\n";
		auto u = q.front(); q.pop();
		for(const auto & mov : movs){
			auto v = comb(u, mov);
			lli hsh = encode(v);
			if(!vis.count(hsh)){
				P[cnt_cycles(v)]++;
				vis.insert(hsh);
				q.push(v);
			}
		}
	}*/

	int sz = 88179840; //vis.size();
	
	//cout << sz << "\n";
	lli ans = 0;
	lli x0 = 10;
	lli x_pow = 1;
	//cout << "{";
	for(int i = 0; i <= n; ++i){
		//if(i) cout << ", ";
		//cout << P[i];
		ans += P[i] * x_pow;
		x_pow *= x0;
	}
	//cout << "}\n";
	ans /= sz;
	cout << (uint64_t)ans << "\n";
	return 0;
}