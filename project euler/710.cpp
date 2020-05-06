#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e6;

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

int main(){
	for(lli i = 43; ; ++i){
		lli t = solveRecurrence({-2+mod, -2+mod, 1, 3, 0}, {0, 0, 1, 0, 2}, i);
		if(t == 0){
			cout << i << "\n";
			return 0;
		}
	}
	return 0;
}