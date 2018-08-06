#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<int> primes;
vector<bool> isPrime;
void sieve(int n){
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	primes.push_back(2);
	int limit = sqrt(n);
	for(int i = 3; i <= n; i += 2){
		if(isPrime[i]){
			primes.push_back(i);
			if(i <= limit){
				for(int j = i * i; j <= n; j += 2 * i){
					isPrime[j] = false;
				}
			}
		}
	}
}

int maxPot(int n, int p){
	int div = p;
	int ans = 0;
	while(div <= n){
		ans += n / div;
		div *= p;
	}
	return ans;
}

int modPow(int a, int b, int m){
	int ans = 1;
	while(b){
		if(b & 1) ans = (ans * a) % m;
		b >>= 1;
		a = (a * a) % m;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int m = 1e6;
	int n;
	cin >> n;
	int ans = 1;
	sieve(n << 1);
	for(int & p : primes){
		int pot = maxPot(2 * n, p) - maxPot(n + 1, p) - maxPot(n, p);
		ans = (ans * modPow(p, pot, m)) % m;
	}
	cout << ans;
	return 0;
}