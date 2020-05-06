#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

int digitSum(lli n){
	int ans = 0;
	while(n){
		ans += n % 10;
		n /= 10;
	}
	return ans;
}

const lli M = 1e15;

int main(){
	set<lli> posible;
	for(int p = 2; p <= 10; ++p){
		for(lli i = 2; ; ++i){
			lli n = power(i, p);
			if(n > M) break;
			if(digitSum(n) == i){
				posible.insert(n);
			}
		}
	}
	int cnt = 1;
	for(lli x : posible){
		cout << cnt++ << " " << x << "\n";
	}
	return 0;
}