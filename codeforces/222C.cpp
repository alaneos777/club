#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> sieve(int n){
	vector<int> lowestPrime(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(int i = 2; i <= n; ++i) lowestPrime[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lowestPrime[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lowestPrime[j] == j) lowestPrime[j] = i;
	return lowestPrime;
}

const int M = 1e7;
const vector<int> lowestPrime = sieve(M);

map<int, int> fact(int n){
	map<int, int> f;
	while(n > 1){
		int p = lowestPrime[n];
		int a = 0;
		while(n % p == 0){
			n /= p;
			a++;
		}
		f[p] = a;
	}
	return f;
}

int power(int a, int b){
	int ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(n), b(m);
	vector<map<int, int>> a_fact(n), b_fact(m);
	map<int, int> num, den, gcd;
	set<int> primes;
	for(int i = 0; i < n; ++i){
		cin >> a[i];
		a_fact[i] = fact(a[i]);
		for(const auto & par : a_fact[i]){
			primes.insert(par.first);
			num[par.first] += par.second;
		}
	}
	for(int i = 0; i < m; ++i){
		cin >> b[i];
		b_fact[i] = fact(b[i]);
		for(const auto & par : b_fact[i]){
			primes.insert(par.first);
			den[par.first] += par.second;
		}
	}
	for(int p : primes){
		gcd[p] = min(num[p], den[p]);
	}
	auto gcd2 = gcd;
	for(int i = 0; i < n; ++i){
		for(const auto & par : a_fact[i]){
			int p, e;
			tie(p, e) = par;
			int dif = min(e, gcd[p]);
			gcd[p] -= dif;
			a[i] /= power(p, dif);
		}
	}
	gcd = gcd2;
	for(int i = 0; i < m; ++i){
		for(const auto & par : b_fact[i]){
			int p, e;
			tie(p, e) = par;
			int dif = min(e, gcd[p]);
			gcd[p] -= dif;
			b[i] /= power(p, dif);
		}
	}
	cout << n << " " << m << "\n";
	for(int ai : a){
		cout << ai << " ";
	}
	cout << "\n";
	for(int bi : b){
		cout << bi << " ";
	}
	cout << "\n";
	return 0;
}