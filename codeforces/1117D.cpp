#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;

/*int ans(int n, int m){
	int cnt = 0;
	for(int i = 0; i < (1<<n); ++i){
		int consec = 0;
		bool test = true;
		for(int j = 0; j < n; ++j){
			int curr = (i >> j)&1;
			if(curr == 0){
				consec++;
			}else{
				if(consec > 0) test &= (consec%m==0);
				consec = 0;
			}
		}
		if(consec > 0) test &= (consec%m==0);
		if(test){
			cnt++;
		}
	}
	return cnt;
}*/

lli go(const vector<lli> & P, const vector<lli> & init, lli n){
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
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		nValue += ans[i] * init[i];
	return nValue % mod;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, m;
	cin >> n >> m;
	vector<lli> init(m, 1), p(m);
	p[m-1] += 1;
	p[0] += 1;
	init[m-1] = 2;
	cout << go(p, init, n-1) << "\n";
	return 0;
}