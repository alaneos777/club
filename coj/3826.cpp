#include <iostream>
#include <vector>
using namespace std;
using lli = long long int;

const lli mod = 1e9+7;

lli solve(const vector<lli> & P, const vector<lli> & init, lli n){
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
		nValue += ans[i] * init[i] % mod;
	return nValue % mod;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli a, b, c, d, n;
	int q;
	cin >> a >> b >> c >> d >> q;
	vector<lli> P = {(a*d-b*c)%mod, b+c};
	if(P[0]<0) P[0] += mod;
	while(q--){
		cin >> n;
		if(n&1){
			cout << solve(P, {1, c}, n/2) << "\n";
		}else{
			cout << solve(P, {0, a}, n/2) << "\n";
		}
	}
	return 0;
}