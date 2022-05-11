#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using lli = long long int;

lli f(ld m, ld b, lli n){
	lli fm = m;
	lli fb = b;
	lli cnt = 0;
	if(m >= 1 || b >= 1){
		cnt += (fm * (n-1) + 2*fb) * n / 2;
		m -= fm;
		b -= fb;
	}
	ld t = m*n + b;
	lli ft = t;
	if(ft >= 1){
		cnt += f(1/m, (t - ft)/m, ft);
	}
	return cnt;
}

lli cnt(ld m, ld b, int l, int r){
	return f(m, b, r+1) - f(m, b, l);
}

int main(){
	int M = 2e6 + 1, N = 1e9;
	map<int, int> Sqrt;
	for(int i = 0; i*M <= N; ++i){
		Sqrt[i*i] = i;
	}
	lli ans = 0;
	int limit = lli(N)*N / M / M;
	for(int k = 1; k <= limit; k+=2){
		int a = (int)floorl(N/sqrtl(k+1));
		int b = (int)floorl(N/sqrtl(k));
		ans += cnt(sqrtl(k+1), 0, M, a) + cnt(0, N, a+1, b) - cnt(sqrtl(k), 0, M, b);
		if(Sqrt.count(k+1)){
			ans -= a-M+1;
		}
		if(Sqrt.count(k)){
			ans += b-M+1;
		}
	}
	cout << ans << "\n";
	return 0;
}