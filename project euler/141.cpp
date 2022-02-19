#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
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

const lli M = 1e12;
const auto lp = sieve(powl(M/2.0, 2.0/3.0) + 1000);

auto divs2(int n){
	int n_ = n;
	vector<pair<int, int>> f;
	while(n_ > 1){
		int p = lp[n_], a = 0;
		while(n_ % p == 0){
			n_ /= p;
			a++;
		}
		f.emplace_back(p, 2*a);
	}
	vector<int> divs;
	function<void(int, int)> dfs = [&](int pos, int div){
		if(pos == f.size()){
			divs.push_back(div);
		}else{
			auto[p, a] = f[pos];
			lli p_pow = 1;
			for(int i = 0; i <= a; ++i){
				if(div*p_pow >= n) break;
				dfs(pos+1, div*p_pow);
				p_pow *= p;
			}
		}
	};
	dfs(0, 1);
	sort(divs.begin(), divs.end());
	return divs;
}

set<lli> isSq;

lli f(lli m){
	lli ans = 0;
	int lim = powl(M/2.0, 2.0/3.0) + 10;
	for(int q = 1; q <= lim; ++q){
		for(int r : divs2(q)){
			lli d = (lli)q*q/r;
			lli N2 = d*q + r;
			if(d <= (m-r)/q && isSq.count(N2)){
				cout << N2 << " = " << d << "*" << q << " + " << r << "\n";
				ans += N2;
			}
		}
	}
	return ans;
}

int main(){
	/*
	N^2 = dq + r
	r < q < d
	dr = q^2
	r | q^2
	dqr = q^3
	(N^2-r)r = q^3
	N^2 = r + q^3/r
	*/
	for(lli i = 1; i*i <= M; ++i){
		isSq.insert(i*i);
	}
	cout << f(M) << "\n";
	return 0;
}