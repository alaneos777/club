#include <bits/stdc++.h>
using namespace std;

vector<int> sieve(int n){
	vector<int> lp(n+1, 1);
	lp[0] = lp[1] = 0;
	for(int i = 2; i <= n; ++i) lp[i] = (i&1 ? i : 2);
	for(int i = 3; i*i <= n; i += 2){
		if(lp[i] == i){
			for(int j = i*i; j <= n; j += 2*i){
				if(lp[j] == j) lp[j] = i;
			}
		}
	}
	return lp;
}
 
const int M = 5e7;
const auto lp = sieve(M);
 
auto fact(int n){
	vector<pair<int, int>> f;
	while(n > 1){
		int p = lp[n];
		int cnt = 0;
		while(n % p == 0){
			n /= p;
			cnt++;
		}
		f.emplace_back(p, cnt);
	}
	return f;
}

auto divs(int n){
	vector<int> divs;
	auto f = fact(n);
	function<void(int, int)> rec = [&](int pos, int acum){
		if(pos == f.size()){
			divs.push_back(acum);
		}else{
			int p, a;
			tie(p, a) = f[pos];
			int p_pow = 1;
			for(int i = 0; i <= a; ++i){
				rec(pos + 1, acum * p_pow);
				p_pow *= p;
			}
		}
	};
	rec(0, 1);
	return divs;
}

int main(){
	int cnt = 0;
	for(int n = 1; n < M; ++n){
		int sols = 0;
		for(int a : divs(n)){
			int e = n/a;
			if((a+e)%4 != 0) continue;
			int r = (a + e) / 4;
			if(a - r <= 0) continue;
			sols++;
			if(sols == 2) break;
		}
		if(sols == 1){
			cnt++;
		}
	}
	cout << cnt << "\n";
	return 0;
}