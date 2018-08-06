#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<lli> primos;
vector<bool> es_primo;

void criba(lli n){
	es_primo.resize(n + 1, true);
	es_primo[0] = es_primo[1] = false;
	for(lli i = 4; i <= n; i += 2) es_primo[i] = false;
	primos.push_back(2);
	lli limit = sqrt(n);
	for(lli i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(lli j = i * i; j <= n; j += 2*i){
					es_primo[j] = false;
				}
			}
		}
	}
}

lli maxPot(lli n, lli p){
	lli div = p;
	lli ans = 0;
	while(div <= n){
		ans += n / div;
		div *= p;
	}
	return ans;
}

void factor_factorial(lli n, map<lli, lli> & f, lli m){
	for(lli & p : primos){
		if(p > n) break;
		f[p] += maxPot(n, p) * m;
	}
}

int main(){
	lli m = 20000000;
	lli n = 15000000;
	criba(m);
	lli ans = 0;
	map<lli, lli> f;
	factor_factorial(m, f, 1);
	factor_factorial(n, f, -1);
	factor_factorial(m - n, f, -1);
	for(auto & pot : f){
		ans += pot.first * pot.second;
	}
	cout << ans << "\n";
	return 0;
}