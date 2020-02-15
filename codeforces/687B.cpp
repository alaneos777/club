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

const int M = 1e6;
const vector<int> lowestPrime = sieve(M);

void fact(map<int, int> & f, int n){
	while(n > 1){
		int p = lowestPrime[n];
		int a = 0;
		while(n % p == 0){
			n /= p;
			a++;
		}
		f[p] = max(f[p], a);
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k, ci;
	cin >> n >> k;
	map<int, int> lcm, f_k;
	for(int i = 0; i < n; ++i){
		cin >> ci;
		fact(lcm, ci);
	}
	fact(f_k, k);
	bool ans = true;
	for(auto par : f_k){
		int p, a;
		tie(p, a) = par;
		if(lcm[p] - a < 0){
			ans = false;
			break;
		}
	}
	if(ans) cout << "Yes\n";
	else cout << "No\n";
	return 0;
}