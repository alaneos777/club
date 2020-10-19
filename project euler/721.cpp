#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const lli mod = 1e9 - 63;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

lli solveRecurrence(const vector<lli> & P, const vector<lli> & init, lli n){
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
				(R[i + j + d] += ans[i] * ans[j]) %= mod;
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				(R[i + j] += R[i + deg] * P[j]) %= mod;
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		(nValue += ans[i] * init[i]) %= mod;
	return nValue;
}

bool isSq[10000000+1];

lli f(lli a){
	lli b = ceil(sqrtl(a));
	lli n = a*a;
	if(isSq[a]) return power(2*b, n);
	return solveRecurrence({a - b*b, 2*b}, {2, 2*b}, n) - 1;
}

int main(){
	for(lli x = 0; x*x <= 10000000; ++x){
		isSq[x*x] = true;
	}
	lli ans = 0;
	lli N = 5000000;
	for(lli a = 1; a <= N; ++a){
		ans = (ans + f(a)) % mod;
	}
	cout << ans << "\n";
	return 0;
}