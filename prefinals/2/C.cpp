#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 998244353;

auto rec(const vector<lli> & P, const vector<lli> & init, lli n){
	int deg = P.size();
	assert(deg == init.size());
	vector<lli> ans(deg), R(2*deg);
	ans[0] = 1;
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), 0);
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				(R[i + j + d] += ans[i] * ans[j]) %= mod;
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				(R[i + j] += R[i + deg] * P[j]) %= mod;
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		(nValue += ans[i] * init[i]) %= mod;
	return make_pair(ans, nValue);
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

vector<lli> gauss(vector<vector<lli>> & A, vector<lli> b){
	int n = A.size(), i = 0, j = 0;
	while(i < n && j < n){
		if(A[i][j] == 0){
			for(int k = i + 1; k < n; k++){
				if(A[k][j] != 0){
					swap(A[i], A[k]);
					swap(b[i], b[k]);
					break;
				}
			}
		}
		if(A[i][j] != 0){
			lli inv_mult = power(A[i][j], mod - 2);
			if(A[i][j] != 1){
				for(int l = 0; l < n; ++l){
					A[i][l] = A[i][l] * inv_mult % mod;
				}
				b[i] = b[i] * inv_mult % mod;
			}
			for(int k = 0; k < n; k++){
				if(k != i && A[k][j] != 0){
					lli inv_adit = (mod - A[k][j]) % mod;
					for(int l = 0; l < n; ++l){
						A[k][l] += inv_adit * A[i][l] % mod;
						if(A[k][l] >= mod) A[k][l] -= mod;
					}
					b[k] += inv_adit * b[i] % mod;
					if(b[k] >= mod) b[k] -= mod;
				}
			}
			i++;
		}
		j++;
	}
	assert(i == n);
	return b;
}

auto mult(const vector<lli> & a, const vector<lli> & b){
	vector<lli> c(a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			(c[i + j] += a[i] * b[j]) %= mod;
		}
	}
	return c;
}

auto shift(const vector<lli> a, const vector<lli> & b){
	int n = a.size();
	lli last = a.back();
	vector<lli> c(n);
	c[0] = last * b[0] % mod;
	for(int i = 1; i < n; ++i){
		c[i] = (a[i-1] + last*b[i]) % mod;
	}
	return c;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	lli m, k;
	cin >> n >> m >> k;
	vector<lli> a(n);
	lli sum = 0;
	for(lli & ai : a){
		cin >> ai;
		sum += ai;
	}
	sum = power(sum, mod - 2);
	for(lli & ai : a){
		ai = ai * sum % mod;
	}
	vector<lli> p = a;
	for(lli & ai : a){
		ai = (mod - ai) % mod;
	}
	reverse(a.begin(), a.end());
	a.push_back(1);
	a = mult(a, {mod - 1, 1});
	a.pop_back();
	for(lli & ai : a){
		ai = (mod - ai) % mod;
	}
	
	vector<lli> rhs(n+1, 1);
	rhs[0] = 0;
	vector<vector<lli>> mat(n+1, vector<lli>(n+1));
	for(int i = 0; i <= n; ++i){
		mat[i][i] = 1;
	}

	vector<vector<lli>> e(n);
	e[n-1] = rec(a, vector<lli>(n+1), m-n+1).first;

	for(int i = n-2; i >= 1; --i){
		e[i] = shift(e[i+1], a);
	}

	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= n; ++j){
			int idx = i-j;
			if(idx >= 0){
				mat[i][idx] -= p[j-1];
				if(mat[i][idx] < 0) mat[i][idx] += mod;
			}else{
				for(int t = 0; t <= n; ++t){
					mat[i][t] -= p[j-1] * e[-idx][t] % mod;
					if(mat[i][t] < 0) mat[i][t] += mod;
				}
			}
		}
	}

	vector<lli> init = gauss(mat, rhs);
	cout << rec(a, init, k).second << "\n";

	return 0;
}