#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct SumPrimePiModulo4{
	int v;
	lli n;
	vector<lli> lo, hi;
	vector<lli> lo1, hi1;
	vector<int> primes;

	SumPrimePiModulo4(lli n): n(n), v(sqrt(n)){
		lo.resize(v+2), hi.resize(v+2);
		lo1.resize(v+2), hi1.resize(v+2);
	}

	void build(){
		lli p, q, j, end, i, d;
		lli temp, temp1;
		for(p = 1; p <= v; p++){
			lo[p] = p - 1;
			hi[p] = n/p - 1;
			lo1[p] = (p + 3) / 4 - 1;
			hi1[p] = (n/p + 3) / 4 - 1;
		}
		for(p = 2; p <= v; p++){
			if(lo[p] == lo[p-1]) continue;
			primes.push_back(p);
			temp = lo[p-1];
			temp1 = lo1[p-1];
			q = p * p;
			end = (v <= n/q) ? v : n/q;
			for(i = 1; i <= end; ++i){
				d = i * p;
				if(d <= v){
					hi[i] -= (hi[d] - temp);
					if(p % 4 == 1)
						hi1[i] -= (hi1[d] - temp1);
					else if(p % 4 == 3)
						hi1[i] -= (hi[d] - hi1[d]) - (temp - temp1);
				}else{
					hi[i] -= (lo[n/d] - temp);
					if(p % 4 == 1)
						hi1[i] -= (lo1[n/d] - temp1);
					else if(p % 4 == 3)
						hi1[i] -= (lo[n/d] - lo1[n/d]) - (temp - temp1);
				}
			}
			for(i = v; i >= q; i--){
				lo[i] -= (lo[i/p] - temp);
				if(p % 4 == 1)
					lo1[i] -= (lo1[i/p] - temp1);
				else if(p % 4 == 3)
					lo1[i] -= (lo[i/p] - lo1[i/p]) - (temp - temp1);
			}
		}
	}

	lli get(lli i) const{
		lli ans = 0;
		if(i <= v) return lo1[i];
		else return hi1[n/i];
	}
};

lli SUM(const SumPrimePiModulo4 & pi, function<lli(lli, int)> g, lli n, int idx = 0){
	lli ans = (pi.primes[idx] <= 2 && 2 <= n);
	if(idx == 0) ans++;
	for(int i = idx; i < pi.primes.size(); ++i){
		lli p = pi.primes[i];
		if(p * p > n) break;
		int e = 1;
		lli curr = n / p;
		while(curr >= p){
			ans += g(p, e) * SUM(pi, g, curr, i+1) + g(p, e+1);
			curr /= p;
			++e;
		}
	}
	return ans;
}

auto h = [&](lli p, int a){
	if(p == 2) return 1ll;
	else if((p & 3) == 3) return lli((a & 1) == 0);
	else{
		if((a & 3) == 0 || (a & 3) == 2) return 1ll;
		else return 0ll;
	}
};

auto g = [&](lli p, int a){
	if(p == 2) return 1ll;
	else if((p & 3) == 3) return lli((a & 1) == 0);
	else{
		if((a & 3) == 0) return 1ll;
		else if((a & 3) == 2) return -1ll;
		else return 0ll;
	}
};

lli forbidden = -1;
auto t = [&](lli p, int a){
	if(p == forbidden) return 0ll;
	if(p == 2) return 1ll;
	else if((p & 3) == 3) return lli((a & 1) == 0);
	else{
		if((a & 3) == 0 || (a & 3) == 2) return 1ll;
		else return 0ll;
	}
};

const lli N = 1e12;
auto pi = SumPrimePiModulo4(N);

lli mod3(lli n){
	return (SUM(pi, h, n) - SUM(pi, g, n)) / 2;
}

lli mod2(lli n){
	lli ans = 0;
	lli m = sqrtl(n);
	for(lli p : pi.primes){
		if(p > m) break;
		if((p & 3) == 1){
			forbidden = p;
			ans += SUM(pi, t, n/p);
		}
	}
	for(lli p = m+1; p <= n/m; ++p){
		bool is = true;
		for(lli d = 2; d*d <= p; ++d){
			if(p % d == 0){
				is = false;
				break;
			}
		}
		if((p & 3) == 1 && is){
			forbidden = p;
			ans += SUM(pi, t, n/p);
		}
	}
	forbidden = -1;
	for(lli i = 1; i < m; ++i){
		ans += (pi.get(n/i) - pi.get(n/(i+1))) * SUM(pi, t, i);
	}
	for(lli p : pi.primes){
		__int128 p4 = (__int128)p*p*p*p;
		if(p4 > n) break;
		if((p & 3) == 1){
			lli nxt = n/p4/p;
			while(nxt){
				forbidden = p;
				ans += SUM(pi, t, nxt);
				nxt /= p4;
			}
		}
	}
	return ans;
}

int main(){
	pi.build();
	cout << mod3(N) + mod2(N) << "\n";
	return 0;
}