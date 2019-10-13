#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

vector<lli> rec(const vector<lli> & P, lli n){
	int deg = P.size();
	vector<lli> ans(deg), R(2*deg);
	ans[0] = 1;
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), 0);
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				R[i + j + d] += ans[i] * ans[j] % mod;
		for(int i = 0; i < 2*deg; ++i) R[i] %= mod;
		for(int i = deg-1; i >= 0; i--){
			R[i + deg] %= mod;
			for(int j = 0; j < deg; j++)
				R[i + j] += R[i + deg] * P[j] % mod;
		}
		for(int i = 0; i < deg; i++) R[i] %= mod;
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	reverse(ans.begin(), ans.end());
	return ans;
}

lli inverse(lli a){
	lli r0 = a, r1 = mod, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(r0 == -1) s0 = -s0;
	if(s0 < 0) s0 += mod;
	return s0;
}

vector<lli> gauss(vector<vector<lli>> A, vector<lli> b){
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
			lli inv_mult = inverse(A[i][j]);
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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int k;
	cin >> k;
	vector<lli> a(k), b(k);
	for(int i = 0; i < k; ++i){
		cin >> a[i];
	}
	reverse(a.begin(), a.end());
	for(int i = 0; i < k; ++i){
		cin >> b[i];
	}
	vector<lli> d = rec(a, b.back());
	vector<vector<lli>> e(k);
	for(int j = 0; j < k; ++j){
		e[j] = rec(a, b.back() - b[j]);
	}
	for(int i = 0; i < k-1; ++i){
		for(int j = i+1; j < k; ++j){
			swap(e[i][j], e[j][i]);
		}
	}
	vector<lli> c = gauss(e, d);
	for(int i = 0; i < k; ++i){
		if(i) cout << " ";
		cout << c[i];
	}
	cout << "\n";
	return 0;
}