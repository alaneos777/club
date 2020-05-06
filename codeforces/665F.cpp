#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> sieve(int n){
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

const int M = 2e6;
const vector<int> primes = sieve(M);

lli N, V;
vector<lli> lo(M), hi(M);
void pre(lli n){
	lli v = sqrt(n), p, temp, q, j, end, i, d;
	for(p = 1; p <= v; p++){
		lo[p] = p - 1;
		hi[p] = n/p - 1;
	}
	for(p = 2; p <= v; p++){
		if(lo[p] == lo[p-1]) continue;
		temp = lo[p-1];
		q = p * p;
		end = (v <= n/q) ? v : n/q;
		for(i = 1; i <= end; ++i){
			d = i * p;
			if(d <= v)
				hi[i] -= hi[d] - temp;
			else
				hi[i] -= lo[n/d] - temp;
		}
		for(i = v; i >= q; i--){
			lo[i] -= lo[i/p] - temp;
		}
	}
}

lli SumPrimePi(lli i){
	if(i <= V) return lo[i];
	else return hi[N/i];
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> N;
	pre(N);
	V = sqrt(N);
	int l = (int)floor(cbrtl(N));
	lli ans = SumPrimePi(l);
	l = (int)floor(sqrtl(N));
	for(int p : primes){
		if(p > l) break;
		ans += SumPrimePi(N/p) - SumPrimePi(p);
	}
	cout << ans << "\n";
	return 0;
}