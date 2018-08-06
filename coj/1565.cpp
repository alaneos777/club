#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<lli> primes;

void sieve(lli n){
	vector<bool> isPrime(n + 1, true);
	primes.push_back(2);
	lli limit = sqrt(n);
	for(lli i = 3; i <= n; i += 2){
		if(isPrime[i]){
			primes.push_back(i);
			if(i <= limit){
				for(lli j = i * i; j <= n; j += 2 * i){
					isPrime[j] = false;
				}
			}
		}
	}
}

lli potInFactorial(lli n, lli p){
	lli div = p, ans = 0;
	while(div <= n){
		ans += n / div;
		div *= p;
	}
	return ans;
}

lli solve(lli n, lli b){
	vector<pair<lli, int>> f;
	for(lli & p : primes){
		if(p * p > b) break;
		int pot = 0;
		while(b % p == 0){
			b /= p;
			++pot;
		}
		if(pot) f.push_back(make_pair(p, pot));
	}
	if(b > 1) f.push_back(make_pair(b, 1));
	lli ret = -1, tmp;
	for(auto & par : f){
		tmp = potInFactorial(n, par.first) / par.second;
		if(ret == -1) ret = tmp;
		else ret = min(ret, tmp);
	}
	return ret;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	sieve(1e6);
	lli n; lli b;
	while(cin >> n >> b && n && b){
		cout << solve(n, b) << "\n";
	}
	return 0;
}