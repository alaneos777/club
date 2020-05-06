#include <bits/stdc++.h>
using namespace std;
using lli = unsigned long long int;

lli k = 3, v, N;

vector<lli> lo, hi;
vector<int> primes;
void pre(lli n){
	v = sqrt(n);
	primes.clear();
	lo = vector<lli>(v+2);
	hi = vector<lli>(v+2);
	lli p, temp, q, j, end, i, d;
	for(p = 1; p <= v; p++){
		lo[p] = p - 1;
		hi[p] = n/p - 1;
	}
	for(p = 2; p <= v; p++){
		if(lo[p] == lo[p-1]) continue;
		primes.push_back(p);
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
	primes.push_back(v+1);
}

lli SumPrimePi(lli i){
	if(i <= v) return lo[i];
	else return hi[N/i];
}

lli g(lli p, lli e){
	return k*e + 1;
}

lli f(lli n, int idx = 0){
	//# of primes between primes[idx] and n
	lli t = SumPrimePi(n) - SumPrimePi(primes[idx] - 1);
	lli ans = t * g(1,1);
	for(int i = idx; i < primes.size(); ++i){
		lli p = primes[i];
		if(p * p > n) break;
		int e = 1;
		lli curr = n / p;
		while(curr >= p){
			ans += g(p, e) * f(curr, i+1) + g(p, e+1);
			curr /= p;
			++e;
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		lli n;
		cin >> n;
		N = n;
		pre(n);
		cout << 1+f(n) << "\n";
	}
	return 0;
}