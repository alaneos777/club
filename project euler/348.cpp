#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

bool pal(lli n){
	lli N = n, n_rev = 0;
	while(n){
		lli d = n % 10;
		n_rev = n_rev * 10 + d;
		n /= 10;
	}
	return N == n_rev;
}

const lli M = 1e9;

int main(){
	map<lli, int> ways;
	for(lli a = 2; a*a <= M; ++a){
		for(lli b = 2; b*b*b <= M; ++b){
			lli n = a*a + b*b*b;
			if(pal(n)){
				ways[n]++;
			}
		}
	}
	int cnt = 0;
	lli sum = 0;
	for(const auto & par : ways){
		lli n; int c;
		tie(n, c) = par;
		if(c == 4){
			sum += n;
			cnt++;
			if(cnt == 5) break;
		}
	}
	cout << sum << "\n";
	return 0;
}