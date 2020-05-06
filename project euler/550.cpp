#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<vector<pair<int, int>>> f(n+1);
	vector<int> cnt(n+1), acum(n+1), primes;
	vector<bool> isPrime(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){ //case base: f(p)
			primes.push_back(i);
			f[i].emplace_back(i, 1);
			cnt[i] = 1;
			acum[i] = i;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0){ //gcd(i, p) != 1
				f[d] = f[i / acum[i]];
				f[d].emplace_back(p, cnt[i] + 1);
				cnt[d] = cnt[i] + 1;
				acum[d] = acum[i] * p;
				break;
			}else{ //gcd(i, p) = 1
				f[d] = f[i];
				f[d].emplace_back(p, 1);
				cnt[d] = 1;
				acum[d] = p;
			}
		}
	}
	return f;
}

const int n = 1e7;
const lli k = 1e12;

const auto lp = sieve(n);
const int mod = 987654321;
const int phi = 619703040;
map<lli, int> mem;

const auto facts = sieve(n+1);

vector<int> getDivs(int n){
	auto f = facts[n];
	vector<int> ans;
	function<void(int, int)> rec = [&](int acum, int pos){
		if(pos == f.size()){
			if(acum != 1 && acum != n){
				ans.push_back(acum);
			}
		}else{
			int p_pw = 1;
			int p; int a;
			tie(p, a) = f[pos];
			for(int i = 0; i <= a; ++i){
				rec(acum * p_pw, pos + 1);
				p_pw *= p;
			}
		}
	};
	rec(1, 0);
	sort(ans.begin(), ans.end());
	return ans;
}

int mex(const vector<int> & a){
	int n = a.size();
	vector<bool> is(n);
	for(int ai : a){
		if(ai < n){
			is[ai] = true;
		}
	}
	for(int i = 0; i < n; ++i){
		if(!is[i]) return i;
	}
	return n;
}

int dp(int n){
	if(n == 1) return 0;
	auto f = facts[n];
	lli hsh = 0;
	vector<int> exps;
	for(const auto & par : f){
		exps.push_back(par.second);
	}
	sort(exps.begin(), exps.end());
	for(int exp : exps){
		hsh = hsh * 100 + exp;
	}
	if(mem.count(hsh)) return mem[hsh];
	vector<int> st;
	auto divs = getDivs(n);
	int sz = divs.size();
	for(int i = 0; i < sz; ++i){
		for(int j = i; j < sz; ++j){
			st.push_back(dp(divs[i]) ^ dp(divs[j]));
		}
	}
	return mem[hsh] = mex(st);
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

void fwt(vector<int> & A, int inv){
	int n = A.size();
	for(int k = 1; k < n; k <<= 1)
		for(int i = 0; i < n; i += k << 1)
			for(int j = 0; j < k; ++j){
				int u = A[i + j], v = A[i + j + k];
				int sum = u + v < mod ? u + v : u + v - mod;
				int rest = u - v < 0 ? u - v + mod : u - v;
				if(inv == -1){
					A[i + j] = sum, A[i + j + k] = rest;
				}else{
					A[i + j] = sum, A[i + j + k] = rest;
				}
			}
	if(inv == -1){
		lli nrev = power(n, phi - 1);
		for(int i = 0; i < n; ++i)
			A[i] = A[i] * nrev % mod;
	}
}

int near(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

int main(){
	vector<int> p;
	for(int i = 2; i <= n; ++i){
		int pos = dp(i);
		if(pos >= p.size()){
			p.resize(pos + 1);
		}
		p[pos]++;
	}
	p.resize(near(p.size()));
	fwt(p, 1);
	for(int & pi : p){
		pi = power(pi, k);
	}
	fwt(p, -1);
	int ans = 0;
	for(int i = 1; i < p.size(); ++i){
		ans = (ans + p[i]) % mod;
	}
	cout << ans << "\n";
	return 0;
}