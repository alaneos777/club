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
	vector<bool> used(v+1);
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

lli solve4(lli n, int idx){
	lli ans = 0;
	for(int i = idx; i < primes.size(); ++i){
		lli p = primes[i];
		lli tmp = SumPrimePi(n/p) - SumPrimePi(p);
		if(tmp <= 0) break;
		ans += tmp;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> N;
	V = sqrt(N);
	pre(N);
	int l = (int)floor(powl(N, 1.0l / 7.0l));
	lli ans = SumPrimePi(l);
	for(lli p : primes){
		lli tmp = SumPrimePi(N/(p*p*p));
		if(p <= N/(p*p*p)) tmp--;
		if(tmp <= 0) break;
		ans += tmp;
	}
	for(int i = 0; i < primes.size(); ++i){
		lli p = primes[i];
		lli tmp = solve4(N/p, i+1);
		if(tmp <= 0) break;
		ans += tmp;
	}
	cout << ans << "\n";
	return 0;
}