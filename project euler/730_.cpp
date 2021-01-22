#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using tup = tuple<int, int, int>;

int countAll(int a, int b, int c, int n){
	if(a+b+c > n) return 0;
	int ans = (a > 0);
	ans += countAll(-2*a+b+2*c, -a+2*b+2*c, -2*a+2*b+3*c, n);
	if(a > 0){
		ans += countAll(2*a+b+2*c, a+2*b+2*c, 2*a+2*b+3*c, n);
	}
	if((a == 0 && b > 0 && b < c) || (a > 0 && b > a)){
		ans += countAll(a-2*b+2*c, 2*a-b+2*c, 2*a-2*b+3*c, n);
	}
	return ans;
}

void sols(int a, int b, int c, int n, set<tup> & spanning){
	if(c > n) return;
	spanning.emplace(a, b, c);
	sols(-2*a+b+2*c, -a+2*b+2*c, -2*a+2*b+3*c, n, spanning);
	if(a > 0){
		sols(2*a+b+2*c, a+2*b+2*c, 2*a+2*b+3*c, n, spanning);
	}
	if((a == 0 && b > 0 && b < c) || (a > 0 && b > a)){
		sols(a-2*b+2*c, 2*a-b+2*c, 2*a-2*b+3*c, n, spanning);
	}
}

set<tup> brute(int k, int n){
	set<tup> ans;
	for(int a = 0; a <= n; ++a){
		for(int b = a; b <= n; ++b){
			for(int c = max(1, b); c <= n; ++c){
				if(__gcd(a, __gcd(b, c)) == 1 && (lli)a*a + (lli)b*b + k == (lli)c*c){
					ans.emplace(a, b, c);
				}
			}
		}
	}
	return ans;
}

set<tup> getGenerators(int k){
	int n = k/2+2;
	set<tup> all = brute(k, n), ans;
	set<tup> spanning;
	for(auto [a, b, c] : all){
		if(spanning.count({a, b, c}) == 0){
			ans.emplace(a, b, c);
			sols(a, b, c, n, spanning);
		}
	}
	return ans;
}

int S(int m, int n){
	int ans = 0;
	for(int k = 0; k <= m; ++k){
		set<tup> R = getGenerators(k);
		for(auto [a, b, c] : R){
			ans += countAll(a, b, c, n);
		}
	}
	return ans;
}

int main(){
	cout << S(100, 1e8) << "\n";
	return 0;
}