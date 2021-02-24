#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;
const lli mod = 1e8;

lli rec(const vector<lli> & P, const vector<lli> & init, lli n){
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

lli ceilSqrt(lli n){
	lli l = 0, r = sqrtl(n)+10, ans = -1;
	while(l <= r){
		lli m = (l + r) / 2;
		if(m*m >= n){
			ans = m;
			r = m-1;
		}else{
			l = m+1;
		}
	}
	return ans;
}

lli nxt(lli n){
	lli k = ceilSqrt(2*n + 1);
	return k*k - n;
}

lli P(lli f, lli r){
	vector<lli> init = {f*f/2};
	if(init.back() == 0) init.back() = 1;
	while(init.size() < 4){
		init.push_back(nxt(init.back()));
	}
	for(lli& x : init) x %= mod;
	return rec({1, -2+mod, 0, 2}, init, r-1);
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

int main(){
	int a = 27, b = 12;
	lli ans = 0;
	for(int i = 0; i <= a; ++i){
		for(int j = 0; j <= b; ++j){
			lli f = power(2, i) * power(3, j);
			lli r = power(2, a-i) * power(3, b-j);
			ans += P(f, r);
			ans %= mod;
		}
	}
	cout << (int)ans << "\n";
	return 0;
}