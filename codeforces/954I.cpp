#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const int mod = 998244353, g = 3;

struct disjointSet{
	int N;
	vector<short int> rank;
	vector<int> parent;

	disjointSet(int N): N(N), parent(N), rank(N){
		iota(parent.begin(), parent.end(), 0);
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

	int size(){
		set<int> st;
		for(int i = 0; i < N; ++i){
			st.insert(parent[i]);
		}
		return st.size();
	}
};

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

void ntt(vector<int>& a, int inv = 1){
	int n = a.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(a[i], a[j]);
	}
	for(int sz = 2; sz <= n; sz <<= 1){
		lli w_1 = powerMod(g, (mod-1)/sz);
		if(inv == -1) w_1 = powerMod(w_1, mod-2);
		vector<lli> w(sz/2, 1);
		for(int j = 1; j < sz/2; ++j){
			w[j] = w[j-1] * w_1 % mod;
		}
		for(int start = 0; start < n; start += sz){
			for(int j = 0; j < sz/2; ++j){
				int u = a[start + j], v = a[start + sz/2 + j] * w[j] % mod;
				a[start + j] = (u+v >= mod ? u+v-mod : u+v);
				a[start + sz/2 + j] = (u-v < 0 ? u-v+mod : u-v);
			}
		}
	}
	if(inv == -1){
		lli inv_n = powerMod(n, mod-2);
		for(int i = 0; i < n; ++i){
			a[i] = inv_n * a[i] % mod;
		}
	}
}

vector<int> operator*(vector<int> a, vector<int> b){
	int m = a.size(), n = b.size(), sz = m+n-1;
	int SZ = nearestPowerOfTwo(sz);
	a.resize(SZ), b.resize(SZ);
	vector<int> c(SZ);
	ntt(a, 1), ntt(b, 1);
	for(int i = 0; i < SZ; ++i){
		c[i] = (lli)a[i] * b[i] % mod;
	}
	ntt(c, -1);
	c.resize(sz);
	return c;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<char> alpha = {'a', 'b', 'c', 'd', 'e', 'f'};
	int r = alpha.size();
	string s, t;
	cin >> s >> t;
	reverse(t.begin(), t.end());
	int m = s.size(), n = t.size();
	vector<disjointSet> ds(m-n+1, r);
	for(int i = 0; i < r; ++i){
		for(int j = 0; j < r; ++j){
			if(i == j) continue;
			vector<int> P(m), Q(n);
			for(int k = 0; k < m; ++k){
				P[k] = (s[k] == alpha[i]);
			}
			for(int k = 0; k < n; ++k){
				Q[k] = (t[k] == alpha[j]);
			}
			vector<int> mult = P * Q;
			for(int k = 0; k <= m-n; ++k){
				if(mult[k + n-1]){
					ds[k].unionSet(i, j);
				}
			}
		}
	}
	for(int k = 0; k <= m-n; ++k){
		cout << r - ds[k].size() << " ";
	}
	cout << "\n";
	return 0;
}