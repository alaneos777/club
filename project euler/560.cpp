#include <bits/stdc++.h>
using namespace std;

const int M = 1e7 + 100;

vector<int> getGrundy(int n){
	vector<int> lp(n+1, 1);
	lp[0] = 0, lp[1] = 1;
	for(int i = 2; i <= n; ++i) lp[i] = (i&1 ? 1 : 0);
	int cnt = 1;
	for(int i = 3; i <= n; i += 2){
		if(lp[i] == 1){
			cnt++;
			for(int j = i; j <= n; j += 2*i){
				if(lp[j] == 1) lp[j] = cnt;
			}
		}
	}
	return lp;
}

const auto grundy = getGrundy(M);

const int mod = 1e9 + 7;

int64_t powerMod(int64_t a, int64_t b){
	int64_t ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

void fwt(vector<int> & A, int inv){
	int n = A.size();
	for(int k = 1; k < n; k <<= 1)
		for(int i = 0; i < n; i += k << 1)
			for(int j = 0; j < k; ++j){
				int u = A[i + j], v = A[i + j + k];
				int sum = u + v < mod ? u + v : u + v - mod;
				int rest = u - v < 0 ? u - v + mod : u - v;
				if(inv == -1){
					A[i + j] = sum, A[i + j + k] = rest;
				}else{
					A[i + j] = sum, A[i + j + k] = rest;
				}
			}
	if(inv == -1){
		int64_t nrev = powerMod(n, mod - 2);
		for(int i = 0; i < n; ++i)
			A[i] = A[i] * nrev % mod;
	}
}

int nearest(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

const int n = 1e7;
const int k = 1e7;

int main(){
	vector<int> p;
	for(int i = 1; i < n; ++i){
		int pos = grundy[i];
		if(pos >= p.size()){
			p.resize(pos+1);
		}
		p[pos]++;
	}
	p.resize(nearest(p.size()));
	fwt(p, 1);
	for(int & pi : p){
		pi = powerMod(pi, k);
	}
	fwt(p, -1);
	cout << p[0] << "\n";
	return 0;
}