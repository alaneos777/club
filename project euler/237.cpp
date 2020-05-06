#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e8;

lli rec(vector<lli> P, vector<lli> init, lli n){
	for(lli & x : P){
		x %= mod;
		if(x < 0) x += mod;
	}
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

int main(){
	cout << rec({1, -2 + mod, 2, 2}, {1, 1, 4, 8}, lli(1e12)-1) << "\n";
	return 0;
}