#include <bits/stdc++.h>
using namespace std;

int count(int M){
	int ans = 0;
	auto count = [&](int a, int b){
		if(b <= M) ans += a/2;
		if(a <= M) ans += max(0, b/2 - (b-a) + 1);
	};
	for(int n = 1; n <= 2*M; ++n){
		for(int m = n+1; m <= 2*M; m += 2){
			if(__gcd(n, m) != 1) continue;
			int a = m*m - n*n;
			int b = 2*m*n;
			if(a > b) swap(a, b);
			if(a > M || b > 2*M) break;
			for(int r = 1; r <= 2*M/b; ++r){
				count(a*r, b*r);
			}
		}
	}
	return ans;
}

int main(){
	int l = 1, r = 10000;
	while(true){
		int m = (l + r) / 2;
		if(count(m) > 1000000){
			if(count(m-1) > 1000000){
				r = m-1;
			}else{
				cout << m << "\n";
				break;
			}
		}else{
			l = m+1;
		}
	}
	return 0;
}