#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli gcd(lli a, lli b){
	lli r;
	while(b) r = a % b, a = b, b= r;
	return a;
}

lli lcm(lli a, lli b){
	return a * (b / gcd(a, b));
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int l, r, x, y;
	cin >> l >> r >> x >> y;
	map<int, int> f;
	for(int n : {x, y}){
		for(int d = 2; d*d <= n; ++d){
			int pot = 0;
			while(n % d == 0) n /= d, ++pot;
			if(pot) f[d] += pot;
		}
		if(n > 1) f[n]++;
	}

	lli ans = 0;
	function<void(map<int, int>::iterator, int)> dfs = [&](map<int, int>::iterator it, lli div){
		if(it == f.end()){
			lli a = div, b = (lli)x * y / div;
			if(l <= a && a <= r && l <= b && b <= r && gcd(a, b) == x && lcm(a, b) == y){
				ans++;
			}
		}else{
			lli p = it->first;
			int a = it->second;
			lli p_pow = 1;
			for(int i = 0; i <= a; ++i){
				auto it2 = it; it2++;
				dfs(it2, div * p_pow);
				p_pow *= p;
			}
		}
	};
	dfs(f.begin(), 1);
	cout << ans << "\n";
	return 0;
}