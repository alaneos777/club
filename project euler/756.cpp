#include <bits/stdc++.h>
using namespace std;
using ld = long double;

/*deque<int> tup;
vector<int> freq;
int cnt = 0;
void gen(int n, int m){
	if(m < 0 || m > n) return;
	if(n == 0){
		cnt++;
		int sz = tup.size();
		for(int i = 1; i <= sz; ++i){
			freq[tup[i-1]] += tup[i-1] - (i > 1 ? tup[i-2] : 0);
		}
	}else{
		tup.push_front(n);
		gen(n-1, m-1);
		tup.pop_front();
		gen(n-1, m);
	}
}*/

auto phiSieve(int n){
	vector<int> primes, lp(n+1), phi(n+1);
	phi[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
			phi[i] = i-1;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p){
				phi[d] = phi[i] * p;
				break;
			}else{
				phi[d] = phi[i] * (p-1);
			}
		}
	}
	return phi;
}

const int n = 12345678, m = 12345;
const auto phi = phiSieve(n);

int main(){
	ld approx = 0, sum = 0;
	ld q = 1 - (ld)m/n;
	for(int i = 1; i <= n; ++i){
		approx += (1 - q) * phi[i];
		sum += phi[i];
		q *= ld(n-i-m) / (n-i);
	}
	ld ans = sum - approx;
	cout << fixed << setprecision(6) << ans << "\n";
	return 0;
}