#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

void fwt(vector<int> & A, int op, int inv){
	int n = A.size();
	for(int k = 1; k < n; k <<= 1)
		for(int i = 0; i < n; i += k << 1)
			for(int j = 0; j < k; ++j){
				int u = A[i + j], v = A[i + j + k];
				int sum = u + v < mod ? u + v : u + v - mod;
				int rest = u - v < 0 ? u - v + mod : u - v;
				if(inv == -1){
					if(op == 0)
						A[i + j + k] = rest ? mod - rest : 0;
					else if(op == 1)
						A[i + j] = rest;
					else if(op == 2)
						A[i + j] = sum, A[i + j + k] = rest;
				}else{
					if(op == 0)
						A[i + j + k] = sum;
					else if(op == 1)
						A[i + j] = sum;
					else if(op == 2)
						A[i + j] = sum, A[i + j + k] = rest;
				}
			}
	if(inv == -1 && op == 2){
		lli nrev = powerMod(n, mod-2);
		for(int i = 0; i < n; ++i)
			A[i] = A[i] * nrev % mod;
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(1<<n), b(1<<n);
	for(int& ai : a) cin >> ai;
	for(int& bi : b) cin >> bi;
	fwt(a, 2, 1);
	fwt(b, 2, 1);
	for(int i = 0; i < (1<<n); ++i){
		a[i] = (lli)a[i] * b[i] % mod;
	}
	fwt(a, 2, -1);
	for(int ai : a){
		cout << ai << " ";
	}
	cout << "\n";
	return 0;
}