#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli N = 1e10;

lli v;
vector<lli> lo, hi;
void pre(lli n){
	v = sqrt(n);
	lli p, temp, q, j, end, i, d;
	lo.resize(v+1), hi.resize(v+1);
	for(p = 1; p <= v; p++){
		lo[p] = p - 1;
		hi[p] = n/p - 1;
	}
	for(p = 2; p <= v; p++){
		if(lo[p] == lo[p-1]) continue;
		temp = lo[p-1];
		q = p * p;
		end = (v <= n/q) ? v : n/q;
		for(i = 1; i <= end; ++i){
			d = i * p;
			if(d <= v)
				hi[i] -= hi[d] - temp;
			else
				hi[i] -= lo[n/d] - temp;
		}
		for(i = v; i >= q; i--){
			lo[i] -= lo[i/p] - temp;
		}
	}
}

lli SumPrimePi(lli i){
	if(i <= v) return lo[i];
	else return hi[N/i];
}

int main(){
	pre(N);
	lli cnt = N;
	for(lli y = 1; y*y <= N; ++y){
		cnt -= SumPrimePi(N/y) - SumPrimePi(y-1);
	}
	cout << cnt << "\n";
	return 0;
}