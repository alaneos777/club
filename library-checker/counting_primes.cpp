#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

template<typename T>
struct SumPrimePi{
	int v;
	lli n;
	vector<T> lo, hi;
	vector<int> primes;

	SumPrimePi(lli n): n(n), v(sqrt(n)){
		lo.resize(v+2), hi.resize(v+2);
	}

	void build(){
		lli p, q, j, end, i, d;
		T temp;
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
					hi[i] -= (hi[d] - temp);
				else
					hi[i] -= (lo[n/d] - temp);
			}
			for(i = v; i >= q; i--){
				lo[i] -= (lo[i/p] - temp);
			}
		}
	}

	T get(lli i) const{
		if(i <= v) return lo[i];
		else return hi[n/i];
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n;
	cin >> n;
	SumPrimePi<lli> pi(n);
	pi.build();
	cout << pi.get(n) << "\n";
	return 0;
}