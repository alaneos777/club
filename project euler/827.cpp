#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 409120391;

__int128_t powerMod(__int128_t a, __int128_t b, __int128_t m){
	a %= m;
	__int128_t ans = 1;
	while(b){
		if(b&1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

bool isPrimeMillerRabin(__int128_t n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	__int128_t d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
		if(n == a) return true;
		__int128_t m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) continue;
		int k = 0;
		for(; k < s; ++k){
			m = m * m % n;
			if(m == n - 1) break;
		}
		if(k == s) return false;
	}
	return true;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
lli aleatorio(lli a, lli b){
	std::uniform_int_distribution<lli> dist(a, b);
	return dist(rng);
}
lli getFactor(lli n){
	lli a = aleatorio(1, n - 1), b = aleatorio(1, n - 1);
	lli x = 2, y = 2, d = 1;
	while(d == 1){
		x = (__int128_t)x * ((x + b) % n) % n + a;
		y = (__int128_t)y * ((y + b) % n) % n + a;
		y = (__int128_t)y * ((y + b) % n) % n + a;
		d = __gcd(abs(x - y), n);
	}
	return d;
}

map<lli, int> fact;
void factorize(lli n, bool clean = true){
	if(clean) fact.clear();
	while(n > 1 && !isPrimeMillerRabin(n)){
		lli f = n;
		for(; f == n; f = getFactor(n));
		n /= f;
		factorize(f, false);
		for(auto&[p, a] : fact){
			while(n % p == 0){
				n /= p;
				++a;
			}
		}
	}
	if(n > 1) ++fact[n];
}

void getDivisors(vector<pair<lli, int>> fact_n, lli n, function<void(const vector<pair<lli, int>>&, const vector<pair<lli, int>>&, lli)> f){
	vector<pair<lli, int>> fact_comp;
	for(auto[p, _] : fact_n){
		fact_comp.emplace_back(p, 0);
	}
	function<void(int, lli)> go = [&](int pos, lli acum){
		if(pos == fact_n.size()){
			f(fact_n, fact_comp, acum);
			return;
		}
		auto[p, a] = fact_n[pos];
		for(int i = a; i >= 0; --i){
			go(pos+1, acum);
			acum /= p;
			fact_n[pos].second--;
			fact_comp[pos].second++;
		}
		fact_n[pos].second = a;
		fact_comp[pos].second = 0;
	};
	go(0, n);
}

auto getUnorderedFactorizations(lli n){
	factorize(n);
	vector<pair<lli, int>> fact_n;
	for(auto[p, a] : fact){
		fact_n.emplace_back(p, a);
	}
	function<vector<vector<lli>>(vector<pair<lli, int>>, lli, lli)> U = [&](vector<pair<lli, int>> fact_n, lli n, lli m) -> vector<vector<lli>>{
		if(n == 1) return {{}};
		if(m == 1) return {};
		vector<vector<lli>> ans;
		getDivisors(fact_n, n, [&](const vector<pair<lli, int>>& fact_d, const vector<pair<lli, int>>& fact_nd, lli d){
			if(d > m) return;
			auto lists = U(fact_nd, n/d, d);
			for(auto& list : lists){
				list.push_back(d);
			}
			ans.insert(ans.end(), lists.begin(), lists.end());
		});
		return ans;
	};
	return U(fact_n, n, n);
}

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i%p == 0) break;
		}
	}
	return primes;
}

const int M = 1e3;
auto primes = sieve(M);
vector<int> primes_1, primes_3;

lli Q(lli n){
	n = 2*(n+1);
	lli np = n, two = 1;
	while(np%2 == 0){
		two *= 2;
		np /= 2;
	}
	auto odd_facts = getUnorderedFactorizations(np);
	vector<vector<lli>> facts;
	for(auto& odd_fact : odd_facts){
		auto fact = odd_fact;
		fact.push_back(two);
		reverse(fact.begin(), fact.end()-1);
		facts.push_back(fact);
		for(int i = 0; i < odd_fact.size(); ++i){
			fact = odd_fact;
			fact.push_back(odd_fact[i]*two);
			fact.erase(fact.begin()+i);
			reverse(fact.begin(), fact.end()-1);
			facts.push_back(fact);
		}
	}
	lli ans = 1;
	double log_min = 1e18;
	for(auto& fact : facts){
		double log_curr = 0;
		lli curr = 1;
		for(int i = 0; i < fact.size()-1; ++i){
			log_curr += log(primes_1[i])*(fact[i]-1)/2;
			curr = curr * powerMod(primes_1[i], (fact[i]-1)/2, mod) % mod;
		}
		auto rem_facts = getUnorderedFactorizations(fact.back()-1);
		for(auto rem_fact : rem_facts){
			double rem_log_curr = 0;
			lli rem_curr = 1;
			reverse(rem_fact.begin(), rem_fact.end());
			for(int j = 0; j < rem_fact.size(); ++j){
				lli expo = (primes_3[j]==2) ? (rem_fact[j]+1)/2 : (rem_fact[j]-1)/2;
				rem_log_curr += log(primes_3[j])*expo;
				rem_curr = rem_curr * powerMod(primes_3[j], expo, mod) % mod;
			}
			if(log_curr + rem_log_curr < log_min){
				log_min = log_curr + rem_log_curr;
				ans = curr * rem_curr % mod;
			}
		}
	}
	return ans;
}

int main(){
	for(int p : primes){
		if(p%4 == 1){
			primes_1.push_back(p);
		}else{
			primes_3.push_back(p);
		}
	}
	lli ans = 0;
	lli ten = 1;
	for(int i = 1; i <= 18; ++i){
		ten *= 10;
		(ans += Q(ten)) %= mod;
	}
	cout << ans << "\n";
	return 0;
}