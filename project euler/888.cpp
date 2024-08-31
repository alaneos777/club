#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int mod = 912491249;

lli power(lli a, lli n){
	lli ans = 1;
	while(n){
		if(n&1) ans = ans * a % mod;
		n >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

vector<int> operator+(const vector<int>& a, const vector<int>& b){
	vector<int> c = a;
	c.resize(max(a.size(), b.size()));
	for(int i = 0; i < b.size(); ++i){
		c[i] += b[i];
		if(c[i] >= mod) c[i] -= mod;
	}
	return c;
}

vector<int> expand(const vector<int>& a, int k){
	if(k&1) return a;
	vector<int> c(a.size());
	for(int i = 0; i < a.size(); ++i){
		c[0] += a[i];
		if(c[0] >= mod) c[0] -= mod;
	}
	return c;
}

vector<int> operator*(const vector<int>& a, lli k){
	vector<int> c(a.size());
	for(int i = 0; i < a.size(); ++i){
		c[i] = k * a[i] % mod;
	}
	return c;
}

void fwt(vector<int>& A, int inv){
	int n = A.size();
	for(int k = 1; k < n; k <<= 1){
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				int u = A[i + j], v = A[i + j + k];
				int sum = u + v < mod ? u + v : u + v - mod;
				int rest = u - v < 0 ? u - v + mod : u - v;
				A[i + j] = sum, A[i + j + k] = rest;
			}
		}
	}
	if(inv == -1){
		lli nrev = power(n, mod-2);
		for(int i = 0; i < n; ++i)
			A[i] = A[i] * nrev % mod;
	}
}

vector<int> operator*(vector<int> a, vector<int> b){
	fwt(a, 1);
	fwt(b, 1);
	for(int i = 0; i < a.size(); ++i){
		a[i] = (lli)a[i] * b[i] % mod;
	}
	fwt(a, -1);
	return a;
}

int mex(const vector<int> & a){
	int n = a.size();
	vector<bool> is(n);
	for(int ai : a){
		if(ai < n){
			is[ai] = true;
		}
	}
	for(int i = 0; i < n; ++i){
		if(!is[i]) return i;
	}
	return n;
}

int main(){
	int lim = 15000, M = 1249;
	vector<int> g(lim+1);
	for(int i = 1; i <= lim; ++i){
		vector<int> v;
		for(int j : {1, 2, 4, 9}){
			if(i-j >= 0) v.push_back(g[i-j]);
		}
		for(int j = 1; j < i; ++j){
			v.push_back(g[j] ^ g[i-j]);
		}
		g[i] = mex(v);
	}
	vector<int> aux(g.size());
	{
		reverse(g.begin(), g.end());
		int i = 1, j = 0;
		while(i < g.size()){
			if(g[i] == g[j])
				aux[i++] = ++j;
			else{
				if(j == 0) aux[i++] = 0;
				else j = aux[j - 1];
			}
		}
		reverse(g.begin(), g.end());
	}
	int non_per_len = aux.end() - max_element(aux.begin(), aux.end()) - 1;
	int per_len = g.size() - non_per_len - *max_element(aux.begin(), aux.end());
	int N = 12491249;
	g.resize(N+1);
	for(int i = lim+1; i <= N; ++i){
		g[i] = g[i - per_len];
	}
	vector<int> F(nearestPowerOfTwo(1 + *max_element(g.begin(), g.end())));
	for(int i = 1; i <= N; ++i){
		F[g[i]]++;
	}
	vector<int> Z(F.size());
	Z[0] = 1;
	vector<int> sum_even = Z;
	vector<int> sum_odd(F.size());
	for(int i = 1; i <= M; ++i){
		int i_inv = power(i, mod-2);
		if(i&1){
			Z = (sum_even * F + sum_odd * N) * i_inv;
			sum_odd = sum_odd + Z;
		}else{
			Z = (sum_odd * F + sum_even * N) * i_inv;
			sum_even = sum_even + Z;
		}
	}
	cout << Z[0] << "\n";
	return 0;
}