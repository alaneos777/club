#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

vector<int> rec(const vector<int>& P, lli n){
	int deg = P.size();
	vector<int> ans(deg);
	vector<lli> R(2*deg);
	ans[0] = 1;
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), 0);
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				(R[i + j + d] += (lli)ans[i] * ans[j]) %= mod;
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				(R[i + j] += R[i + deg] * P[j]) %= mod;
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	return ans;
}

void gauss(vector<vector<int>>& A, vector<int>& b){
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
}

vector<int> mult(const vector<int>& a, const vector<int>& b){
	vector<int> c(a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			int& pos = c[i+j];
			pos += (lli)a[i] * b[j] % mod;
			if(pos >= mod) pos -= mod;
		}
	}
	return c;
}

vector<int> transform(vector<int> p){
	reverse(p.begin(), p.end());
	for(int& pi : p){
		pi = (mod - pi) % mod;
	}
	p.push_back(1);
	p = mult(p, {mod-1, 1});
	p.pop_back();
	for(int& pi : p){
		pi = (mod - pi) % mod;
	}
	return p;
}

vector<int> shift(const vector<int>& a, const vector<int>& poly){
	vector<int> c;
	lli last = a.back();
	for(int pi : poly){
		c.push_back(pi * last % mod);
	}
	for(int i = 0; i < (int)a.size()-1; ++i){
		c[i+1] += a[i];
		if(c[i+1] >= mod) c[i+1] -= mod;
	}
	return c;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n; lli m, k;
	cin >> n >> m >> k;
	vector<int> p(n);
	lli den = 0;
	for(int& pi : p){
		cin >> pi;
		den += pi;
	}
	den = power(den, mod-2);
	for(int& pi : p){
		pi = pi * den % mod;
	}
	vector<int> poly = transform(p);
	vector<vector<int>> mp(n-1);
	if(n > 1){
		mp[0] = rec(poly, m-n+1);
		for(lli N = m-n+2; N < m; ++N){
			mp[N-(m-n+1)] = shift(mp[N-1-(m-n+1)], poly);
		}
	}
	vector<vector<int>> A(n+1, vector<int>(n+1));
	vector<int> b(n+1);
	A[0][0] = 1;
	for(int i = 1; i <= n; ++i){
		A[i][i] = 1;
		b[i] = 1;
		for(int j = 1; j <= n; ++j){
			lli idx = i-j;
			if(idx >= 0){
				A[i][idx] -= p[j-1];
				if(A[i][idx] < 0) A[i][idx] += mod;
			}else{
				idx += m;
				for(int k = 0; k <= n; ++k){
					A[i][k] -= (lli)p[j-1]*mp[idx-(m-n+1)][k] % mod;
					if(A[i][k] < 0) A[i][k] += mod;
				}
			}
		}
	}
	gauss(A, b);
	lli ans = 0;
	vector<int> Cn = rec(poly, k);
	for(int i = 0; i <= n; ++i){
		(ans += (lli)Cn[i]*b[i]) %= mod;
	}
	cout << ans << "\n";
	return 0;
}