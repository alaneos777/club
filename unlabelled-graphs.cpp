#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
const lli mod = 998244353;
using pii = pair<int, int>;

const int M = 5000;
int fact[M+1], ncr[M+1][M+1];

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

vector<int> operator*(const vector<int> & a, const vector<int> & b){
	vector<int> c(a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			c[i+j] += (lli)a[i]*b[j] % mod;
			if(c[i+j] >= mod) c[i+j] -= mod;
		}
	}
	return c;
}

vector<int> operator+(const vector<int> & a, const vector<int> & b){
	vector<int> c(max(a.size(), b.size()));
	for(int i = 0; i < c.size(); ++i){
		c[i] = (i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0);
		if(c[i] >= mod) c[i] -= mod;
	}
	return c;
}

vector<int> cnt_cycles(const vector<int> & pi, int n){
	vector<bool> vis(n*n);
	vector<int> cnt(n*(n-1)/2+1);
	for(int i = 0; i < n-1; ++i){
		for(int j = i+1; j < n; ++j){
			if(!vis[i*n+j]){
				int u = i*n+j;
				int len = 0;
				do{
					vis[u] = true;
					u = pi[u];
					int ip = u/n, jp = u%n;
					if(ip > jp) swap(ip, jp);
					u = ip*n + jp;
					len++;
				}while(u != i*n+j);
				cnt[len]++;
			}
		}
	}
	return cnt;
}

map<vector<int>, int> cycle_index_pair(int n){
	vector<int> pi(n);
	iota(pi.begin(), pi.end(), 0);
	map<vector<int>, int> ans;
	do{
		vector<int> sigma(n*n);
		for(int i = 0; i < n-1; ++i){
			for(int j = i+1; j < n; ++j){
				sigma[i*n + j] = pi[i]*n + pi[j];
				sigma[j*n + i] = pi[j]*n + pi[i];
			}
		}
		ans[cnt_cycles(sigma, n)]++;
	}while(next_permutation(pi.begin(), pi.end()));
	return ans;
}

vector<int> all_unlabelled_graphs(int n){
	vector<int> ans = {0};
	for(const auto & a : cycle_index_pair(n)){
		const vector<int> & c = a.first;
		int coef = a.second;
		vector<int> Z = {coef};
		for(int i = 1; i <= n*(n-1)/2; ++i){
			if(c[i] == 0) continue;
			// P = (1+x^i)^c[i]
			vector<int> P(i*c[i]+1);
			for(int j = 0; j <= c[i]; ++j){
				P[i*j] = ncr[c[i]][j];
			}
			Z = Z * P;
		}
		ans = ans + Z;
	}
	int inv = power(fact[n], mod-2);
	for(int & x : ans){
		x = (lli)x * inv % mod;
	}
	return ans;
}

int main(){
	fact[0] = 1;
	for(int i = 1; i <= M; ++i){
		fact[i] = (lli)i * fact[i-1] % mod;
	}
	ncr[0][0] = 1;
	for(int i = 1; i <= M; ++i){
		ncr[i][0] = ncr[i][i] = 1;
		for(int j = 1; j < i; ++j){
			ncr[i][j] = (ncr[i-1][j-1] + ncr[i-1][j]) % mod;
		}
	}
	int n;
	cin >> n;
	vector<int> graphs = all_unlabelled_graphs(n);
	for(lli x : graphs){
		cout << x << " ";
	}
	cout << "\n";
	return 0;
}