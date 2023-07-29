#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto lpSieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			lp[i] = i;
			primes.push_back(i);
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return lp;
}

const int M = 1234567;
const auto lp = lpSieve(M+1);

void factorize(int n, map<int, int>& f){
	while(n > 1){
		int p = lp[n], a = 0;
		while(n % p == 0){
			n /= p;
			++a;
		}
		f[p] += a;
	}
}

lli T(int n){
	map<int, int> f;
	factorize(n, f);
	factorize(n-1, f);
	lli ans = 0;
	function<void(map<int, int>::iterator, lli)> go = [&](map<int, int>::iterator it, lli d){
		if(it == f.end()){
			lli m = d - n;
			if(m > 0){
				ans += m;
			}
		}else{
			auto[p, a] = *it;
			lli p_pow = 1;
			auto it2 = it; ++it2;
			for(int i = 0; i <= a; ++i){
				if(p != 2 || i == 0 || i == a) go(it2, d * p_pow);
				p_pow *= p;
			}
		}
	};
	go(f.begin(), 1);
	return ans;
}

lli U(int n){
	lli ans = 0;
	for(int i = 3; i <= n; ++i){
		ans += T(i);
	}
	return ans;
}

int main(){
	cout << U(M) << "\n";
	return 0;
}