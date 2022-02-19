#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int tab[49];

int conv(int n){
	int ans = 0;
	int p_pow = 1;
	while(n){
		int d = n&1;
		if(d) ans += p_pow;
		n >>= 1;
		p_pow *= 7;
	}
	return ans;
}

const lli u = power(3, (mod-1)/7);
lli w[7];
using poly = vector<int>;

void fwt(poly& A, int inv = 1){
	int n = A.size();
	int tmp[7];
	for(int sz = 7; sz <= n; sz *= 7){
		for(int start = 0; start < n; start += sz){
			for(int j = 0; j < sz/7; ++j){
				for(int k = 0; k < 7; ++k){
					tmp[k] = A[start+j+sz/7*k];
				}
				for(int k = 0; k < 7; ++k){
					int s = 0;
					for(int l = 0; l < 7; ++l){
						int idx = tab[k*l];
						if(inv == -1 && idx != 0) idx = 7 - idx;
						s += tmp[l]*w[idx] % mod;
						if(s >= mod) s -= mod;
					}
					A[start+j+sz/7*k] = s;
				}
			}
		}
	}
	if(inv == -1){
		lli n_rev = power(n, mod-2);
		for(int& ai : A){
			ai = ai * n_rev % mod;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(int i = 0; i < 49; ++i){
		tab[i] = i%7;
	}
	w[0] = 1;
	for(int i = 1; i < 7; ++i){
		w[i] = w[i-1] * u % mod;
	}
	int n; lli k;
	cin >> n >> k;
	poly freq(power(7, 7));
	for(int i = 0; i < n; ++i){
		int ai, ci;
		cin >> ai;
		ci = conv(ai);
		freq[ci]++;
	}
	fwt(freq);
	for(int& fi : freq){
		fi = power(fi, k);
	}
	fwt(freq, -1);
	cout << freq[0] << "\n";
	return 0;
}