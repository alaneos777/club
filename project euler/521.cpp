#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9;

lli gauss(lli n){
	if(n & 1){
		return ((n+1)/2 % mod) * (n % mod) % mod;
	}else{
		return (n/2 % mod) * ((n+1) % mod) % mod;
	}
}

inline lli modula(lli n){
	while(n >= mod) n -= mod;
	while(n < 0) n += mod;
	return n;
}

lli SumPrimePi(lli n){
	lli v = sqrt(n), p, temp, Temp, q, j, end, i, d;
	vector<lli> Lo(v+2), Hi(v+2), lo(v+2), hi(v+2);
	lli ans = 0;
	for(p = 1; p <= v; p++){
		Lo[p] = gauss(p) - 1;
		Hi[p] = gauss(n/p) - 1;
		lo[p] = (p - 1) % mod;
		hi[p] = (n/p - 1) % mod;
	}
	for(p = 2; p <= v; p++){
		if(Lo[p] == Lo[p-1]) continue;
		Temp = Lo[p-1];
		temp = lo[p-1];
		q = p * p;
		end = (v <= n/q) ? v : n/q;
		for(i = 1; i <= end; i++){
			d = i * p;
			if(d <= v){
				Hi[i] = modula(Hi[i] - p * (Hi[d] - Temp) % mod);
				hi[i] = modula(hi[i] - (hi[d] - temp));
				if(i == 1) ans = modula(ans + p * (hi[d] - temp) % mod);
			}else{
				Hi[i] = modula(Hi[i] - p * (Lo[n/d] - Temp) % mod);
				hi[i] = modula(hi[i] - (lo[n/d] - temp));
				if(i == 1) ans = modula(ans + p * (lo[n/d] - temp) % mod);
			}
		}
		for(i = v; i >= q; i--){
			Lo[i] = modula(Lo[i] - p * (Lo[i/p] - Temp) % mod);
			lo[i] = modula(lo[i] - (lo[i/p] - temp));
		}
	}
	return modula(Hi[1] + ans);
}

int main(){
	lli n = 1e12;
	cout << SumPrimePi(n) << "\n";
	return 0;
}