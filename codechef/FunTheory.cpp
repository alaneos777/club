#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli mod = 1e9 + 7;
lli inv = 500000004;

lli modPow(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = (ans * a) % m;
		b >>= 1;
		a = (a * a) % m;
	}
	return ans;
}

vector<lli> primes;
vector<bool> isPrime;
void primesSieve(lli n){
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	primes.push_back(2);
	for(lli i = 4; i <= n; i += 2){
		isPrime[i] = false;
	}
	for(lli i = 3; i <= n; i += 2){
		if(isPrime[i]){
			primes.push_back(i);
			for(lli j = i * i; j <= n; j += 2 * i){
				isPrime[j] = false;
			}
		}
	}
}

vector<pair<lli, int>> factorize(lli n){
	vector<pair<lli, int>> f;
	for(lli & p : primes){
		if(p * p > n) break;
		int pot = 0;
		while(n % p == 0){
			pot++;
			n /= p;
		}
		if(pot) f.push_back(make_pair(p, pot));
	}
	if(n > 1) f.push_back(make_pair(n, 1));
	return f;
}

lli phi(lli n){
	lli ans = n;
	vector<pair<lli, int>> f = factorize(n);
	for(auto & factor : f){
		ans -= ans / factor.first;
	}
	return ans;
}

lli multiplicativeOrder(lli x, lli m){
	lli order = phi(m);
	vector<pair<lli, int>> f = factorize(order);
	for(auto & factor : f){
		lli p = factor.first;
		int a = factor.second;
		order /= pow(p, a);
		lli tmp = modPow(x, order, m);
		while(tmp != 1){
			tmp = modPow(tmp, p, m);
			order *= p;
		}
	}
	return order;
}

int main(){
	ios_base::sync_with_stdio(0);
	primesSieve(1e4);
	int t;
	lli a, c, m, k;
	cin >> t;
	while(t--){
		cin >> a >> c >> m >> k;
		lli order = multiplicativeOrder(a, m);
		lli n = sqrt(order) + 1;
		lli an = modPow(a, n, m);
		lli ans = 0;
		unordered_map<lli, vector<lli>> firstHalf;
		set<lli> solutions;
		lli current = an;
		for(lli p = 1; p <= n; p++){
			firstHalf[current].push_back(p);
			current = (current * an) % m;
		}
		current = c;
		for(lli q = 0; q <= n; q++){
			if(firstHalf.count(current)){
				for(lli & p : firstHalf[current]){
					lli x = n * p - q;
					if(x < order){
						solutions.insert(x);
					}
				}
			}
			current = (current * a) % m;
		}
		//sol + order * (k - 1)
		if(solutions.size()){
			lli sol = *solutions.begin();
			cout << k * (sol + order * (k - 1) % mod * inv % mod) % mod << "\n";
		}else{
			cout << "0\n";
		}
	}
	return 0;
}