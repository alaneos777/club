#include <bits/stdc++.h>
using namespace std;
using lli = uint64_t;

lli gauss(lli n){
	if(n & 1){
		return (n+1)/2 * n;
	}else{
		return n/2 * (n+1);
	}
}

lli SumPrimePi(lli n){
	lli v = sqrt(n), p, temp, Temp, q, j, end, i, d;
	vector<lli> Lo(v+2), Hi(v+2), lo(v+2), hi(v+2);
	lli ans = 0;
	for(p = 1; p <= v; p++){
		Lo[p] = gauss(p) - 1;
		Hi[p] = gauss(n/p) - 1;
		lo[p] = p - 1;
		hi[p] = n/p - 1;
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
				Hi[i] -= p * (Hi[d] - Temp);
				hi[i] -= (hi[d] - temp);
				if(i == 1) ans += p * (hi[d] - temp);
			}else{
				Hi[i] -= p * (Lo[n/d] - Temp);
				hi[i] -= (lo[n/d] - temp);
				if(i == 1) ans += p * (lo[n/d] - temp);
			}
		}
		for(i = v; i >= q; i--){
			Lo[i] -= p * (Lo[i/p] - Temp);
			lo[i] -= (lo[i/p] - temp);
		}
	}
	return Hi[1] + ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli n;
		cin >> n;
		cout << SumPrimePi(n) << "\n";
	}
	return 0;
}