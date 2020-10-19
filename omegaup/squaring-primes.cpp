#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;
const lli inv_6 = 166666668;

inline lli sum2(lli n){
	n %= mod;
	return n * (n + 1) % mod * (2*n + 1) % mod * inv_6 % mod;
}

lli pi_2(lli N){
	int m = sqrt(N);
	vector<int> lo(m+1), hi(m+1);
	auto at = [&](lli x) -> int&{
		if(x <= m) return lo[x];
		else return hi[N / x];
	};
	vector<lli> values;
	for(int i = 1; i <= m; ++i){
		values.push_back(i);
		if(N / i != i) values.push_back(N / i);
	}
	sort(values.begin(), values.end(), greater<lli>());
	for(lli n : values){
		at(n) = sum2(n) - 1;
	}
	for(lli p = 2; p <= m; ++p){
		if(at(p) == at(p - 1)) continue;
		for(lli n : values){
			lli p2 = p*p;
			if(n < p2) break;
			p2 %= mod;
			at(n) = at(n) - (at(n / p) - at(p - 1)) * p2 % mod;
			while(at(n) >= mod) at(n) -= mod;
			while(at(n) < 0) at(n) += mod;
		}
	}
	return at(N);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli N;
	while(cin >> N){
		cout << pi_2(N) << "\n";
	}
	return 0;
}