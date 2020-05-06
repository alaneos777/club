#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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

const int M = 1e8;
const auto lp = sieve(M);
bitset<M> appears;

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

auto getDivs(int n){
	auto f = fact(n);
	vector<lli> divs;
	function<void(int, lli)> dfs = [&](int pos, lli acum){
		if(pos == f.size()){
			divs.push_back(acum);
		}else{
			lli p_pow = 1;
			lli p; int e;
			tie(p, e) = f[pos];
			for(int i = 0; i <= 2*e; ++i){
				dfs(pos+1, acum * p_pow);
				p_pow *= p;
			}
		}
	};
	dfs(0, 1);
	sort(divs.begin(), divs.end());
	return divs;
}

int main(){
	vector<int> primes;
	for(int p = 2; p <= M; ++p){
		if(p != lp[p]) continue;
		primes.push_back(p);
		appears[p] = true;
	}
	lli sum = 0;
	for(int p : primes){
		auto divs = getDivs(p+1);
		for(lli x : divs){
			lli y = lli(p+1) * lli(p+1) / x;
			if(x == y) break;
			if(x-1 <= M && y-1 <= M && appears[x-1] && appears[y-1]){
				//cout << x-1 << " " << p << " " << y-1 << "\n";
				sum += x-1 + p + y-1;
			}
		}
	}
	cout << sum << "\n";
	return 0;
}