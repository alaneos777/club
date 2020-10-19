#include <bits/stdc++.h>
using namespace std;
using LLI = __int128_t;

const int64_t M = int64_t(1e18);
const int T1 = 1e7;
const int T2 = 5e8;

vector<vector<int>> divsSieve(int n){
	vector<vector<int>> ans(n+1);
	for(int i = 2; i <= n; ++i){
		if(!(i % 6 == 1 || i % 6 == 5)) continue;
		for(int j = i; j <= n; j += i){
			ans[j].push_back(i);
		}
	}
	return ans;
}

const vector<vector<int>> divs = divsSieve(T1);

void getFacts(int m, int n, vector<vector<int>> & ans, const vector<int> & acum){
	if(n == 1){
		ans.emplace_back(acum);
		return;
	}
	for(int d : divs[n]){
		if(d <= m){
			auto cp = acum;
			cp.push_back(d);
			getFacts(d, n/d, ans, cp);
		}else{
			break;
		}
	}
}

vector<bool> is;
vector<int> primes, pi;
void sieve(int n){
	is.resize(n+1, true);
	pi.resize(n+1);
	is[0] = is[1] = false;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	for(int i = 1; i <= n; ++i){
		pi[i] = pi[i-1] + is[i];
	}
}

LLI power(LLI a, LLI b){
	LLI ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

int raiz(int64_t y, int k){
	//x^k <= y
	int xx = powl(y, 1.0l / k);
	for(int x = xx+1; x >= xx-1 && x >= 0; --x){
		if(k*logl(x) <= logl(y) && power(x, k) <= y) return x;
	}
	cout << "!" << y << " " << k << "\n";
	assert(0);
	return -1;
}

int64_t rec(int prev, const set<int> & used, int pos, const vector<int> & fact, int64_t lim){
	if(pos == fact.size()-1){
		int idx = raiz(lim, fact[pos]);
		int64_t ans = pi[idx];
		if(prev == -1){
			for(int x : used){
				if(primes[x] <= idx) ans--;
			}
		}else{
			ans -= pi[primes[prev]];
			for(int x : used){
				if(primes[x] > primes[prev] && primes[x] <= idx) ans--;
			}
		}
		return max(0ll, ans);
	}else{
		int64_t ans = 0;
		for(int i = prev+1; i < primes.size(); ++i){
			if(used.count(i)) continue;
			int p = primes[i];
			if(logl(p)*fact[pos] > logl(lim)) break;
			auto cp = used;
			cp.insert(i);
			ans += rec(fact[pos] == fact[pos+1] ? i : -1, cp, pos+1, fact, lim / power(p, fact[pos]));
		}
		return ans;
	}
}

int main(){
	sieve(T2);
	int64_t ans = 1;
	for(int n = 7; n <= T1; n += 6){
		vector<vector<int>> facts;
		getFacts(n, n, facts, vector<int>());
		for(auto fact : facts){
			for(int & x : fact){
				x = (x - 1) / 2;
			}
			int64_t inc = rec(-1, {}, 0, fact, M);
			ans += inc;
			if(inc){
				cout << n << ": " << inc << "\n";
				for(int x : fact) cout << x << " ";cout << "\n\n";
			}
		}
	}
	cout << ans << "\n";
	return 0;
}

//793525366