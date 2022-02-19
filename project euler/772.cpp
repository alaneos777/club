#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

/*using vv = vector<vector<int>>;
const int M = 200;
vv mem[M+1][10];
bool calc[M+1][10];

vv f(int n, int last){
	if(n == 0) return {{}};
	if(last == 0 || n < 0) return {};
	bool& c = calc[n][last];
	vv& ans = mem[n][last];
	if(c) return ans;
	c = true;
	ans = f(n-last, last);
	for(auto& vec : ans){
		vec.push_back(last);
	}
	auto rhs = f(n, last-1);
	ans.insert(ans.end(), rhs.begin(), rhs.end());
	return ans;
}

bool bal(const vector<int>& v){
	int n = v.size();
	int M = 0;
	for(int vi : v){
		M += vi;
	}
	vector<vector<bool>> calc(n, vector<bool>(2*M+1));
	vector<vector<bool>> mem(n, vector<bool>(2*M+1));
	function<bool(int, int)> f = [&](int pos, int sum) -> bool{
		if(pos == n) return sum==0;
		if(calc[pos][sum+M]) return mem[pos][sum+M];
		calc[pos][sum+M] = true;
		return mem[pos][sum+M] = f(pos+1, sum-v[pos]) || f(pos+1, sum+v[pos]);
	};
	return f(0, 0);
}*/

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

int f(int k){
	auto primes = sieve(k);
	lli ans = 2;
	for(int p : primes){
		lli p_pow = 1;
		while(p_pow*p <= k){
			p_pow *= p;
		}
		ans = ans * p_pow % mod;
	}
	return ans;
}

int main(){
	/*for(int n = 2; n <= M; n += 2){
		bool b = true;
		for(const auto &v : f(n, 6)){
			b &= bal(v);
			if(!b) break;
		}
		cout << n;
		if(b) cout << "!";
		cout << "\n";
	}*/
	cout << f(1e8) << "\n";
	return 0;
}