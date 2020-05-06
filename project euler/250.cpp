#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e16;
const int M = 250250;
const int d = 250;

lli power(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

auto mult(const vector<lli> & a, int s){
	vector<lli> c(d);
	for(int i = 0; i < d; ++i){
		int j = i + s;
		if(j >= d) j -= d;
		c[j] = a[i];
	}
	return c;
}

int main(){
	vector<lli> P(d);
	P[0] = 1;
	for(int i = 0; i < M; ++i){
		int si = power(i+1, i+1, d);
		vector<lli> Q = mult(P, si);
		for(int i = 0; i < d; ++i){
			P[i] += Q[i];
			if(P[i] >= mod) P[i] -= mod;
		}
	}
	cout << P[0]-1 << "\n";
	return 0;
}