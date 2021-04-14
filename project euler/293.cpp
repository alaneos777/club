#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<bool> is;
vector<int> primes;

void sieve(int n){
	is.resize(n+1, true);
	is[0] = is[1] = false;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
}

int main(){
	int L = 1e9;
	sieve(L + 1e5);
	vector<int> admissible;
	function<void(int, lli)> f = [&](int pos, int acum){
		lli p = primes[pos], p_pow = p;
		while(true){
			lli nxt = acum * p_pow;
			if(nxt > L) break;
			admissible.push_back(nxt);
			f(pos+1, nxt);
			p_pow *= p;
		}
	};
	f(0, 1);
	sort(admissible.begin(), admissible.end());
	set<int> fortunate;
	for(int x : admissible){
		int y = x + 2;
		while(!is[y]) y++;
		fortunate.insert(y-x);
	}
	int sum = 0;
	for(int f : fortunate){
		sum += f;
	}
	cout << sum << "\n";
	return 0;
}