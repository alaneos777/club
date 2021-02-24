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

void gen_partitions(int n, function<void(const vector<int>&)> f){
	vector<int> a(n);
	int k = 1, y = n-1;
	while(k != 0){
		int x = a[k-1] + 1;
		k--;
		while(2*x <= y){
			a[k] = x;
			y -= x;
			k++;
		}
		int l = k+1;
		while(x <= y){
			a[k] = x;
			a[l] = y;
			f(vector<int>(a.begin(), a.begin() + k+2));
			x++;
			y--;
		}
		a[k] = x+y;
		y = x+y-1;
		f(vector<int>(a.begin(), a.begin() + k+1));
	}
}

int lcm(int a, int b){
	return a / __gcd(a, b) * b;
}

map<vector<int>, int> cycle_index_pair_fast(int n){
	map<vector<int>, int> ans;
	gen_partitions(n, [&](const vector<int> & part){
		vector<int> j(n+1);
		for(int p : part){
			j[p]++;
		}
		lli den = 1;
		for(int i = 1; i <= n; ++i){
			den = den * power(i, j[i]) % mod * fact[j[i]] % mod;
		}

		vector<int> c(n*(n-1)/2+1);
		for(int i = 1; 2*i+1 <= n; ++i){
			c[2*i+1] += i*j[2*i+1];
		}
		for(int i = 1; 2*i <= n; ++i){
			c[i] += j[2*i];
			c[2*i] += (i-1)*j[2*i];
		}
		for(int i = 1; i <= n; ++i){
			c[i] += i*j[i]*(j[i]-1)/2;
		}
		for(int r = 1; r <= n; ++r){
			for(int t = r+1; t <= n; ++t){
				if(lcm(r, t) < c.size()) c[lcm(r, t)] += __gcd(r, t) * j[r]*j[t];
			}
		}
		(ans[c] += fact[n] * power(den, mod-2) % mod) %= mod;
	});
	return ans;
}

vector<int> all_unlabelled_graphs(int n){
	vector<int> ans = {0};
	for(const auto & a : cycle_index_pair_fast(n)){
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