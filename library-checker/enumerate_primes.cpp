#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<bool> is;
vector<int> primes;
void sieve(int n){
	is.resize(n+1, true);
	is[0] = is[1] = false;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, a, b;
	cin >> n >> a >> b;
	sieve(n);
	int pi = 0;
	for(int i = 1; i <= n; ++i){
		pi += is[i];
	}
	vector<int> ans;
	for(int i = 0; a*i+b < primes.size() && primes[a*i+b] <= n; ++i){
		ans.push_back(primes[a*i+b]);
	}
	cout << pi << " " << ans.size() << "\n";
	for(int ai : ans){
		cout << ai << " ";
	}
	cout << "\n";
	return 0;
}