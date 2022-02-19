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

const int M = 2e6;
const auto lp = lpSieve(M+1);

void getFact(map<int, int>& f, int n){
	while(n > 1){
		int p = lp[n], a = 0;
		while(n % p == 0){
			a++;
			n /= p;
		}
		f[p] += a;
	}
}

auto divs(int n){
	vector<lli> divs;
	map<int, int> f;
	getFact(f, n-1);
	getFact(f, n+1);
	lli LIM = ((lli)n*n - 1) / (2*n+1);
	function<void(map<int, int>::iterator, lli)> dfs = [&](map<int, int>::iterator pos, lli div){
		if(pos == f.end()){
			divs.push_back(div);
		}else{
			auto[p, a] = *pos;
			lli p_pow = 1;
			auto pos2 = pos; ++pos2;
			for(int i = 0; i <= a; ++i){
				lli next = div * p_pow;
				if(next > LIM) break;
				dfs(pos2, next);
				p_pow *= p;
			}
		}
	};
	dfs(f.begin(), 1);
	sort(divs.begin(), divs.end());
	return divs;
}

int main(){
	lli ans = 0;
	for(int p = 2; p <= M; ++p){
		for(lli d : divs(p)){
			lli e = ((lli)p*p - 1) / d;
			lli r = p-d;
			lli q = e-p;
			//cout << "(" << p << ", " << q << ") -> " << r << "\n";
			ans += p+q;
		}
	}
	cout << ans << "\n";
	return 0;
}