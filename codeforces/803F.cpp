#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int M = 1e5;
const lli mod = 1e9 + 7;

vector<int> muSieve(int n){
	vector<int> Mu(n + 1, -1);
	Mu[0] = 0, Mu[1] = 1;
	for(int i = 2; i <= n; ++i)
		if(Mu[i])
			for(int j = 2*i; j <= n; j += i)
				Mu[j] -= Mu[i];
	return Mu;
}

const vector<int> Mu = muSieve(M);

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> freq(M+1);
	for(int i = 0; i < n; ++i){
		int ai;
		cin >> ai;
		freq[ai]++;
	}
	vector<int> f(M+1);
	for(int i = 1; i <= M; ++i){
		for(int j = i; j <= M; j += i){
			f[i] += freq[j];
		}
	}
	lli ans = 0;
	for(int i = 1; i <= M; ++i){
		(ans += Mu[i] * (power(2, f[i]) - 1)) %= mod;
		if(ans < 0) ans += mod;
	}
	cout << ans << "\n";
	return 0;
}