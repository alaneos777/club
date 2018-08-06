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

lli pow(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

lli squareFree(lli n, lli r){
	map<lli, lli> f;
	lli ans = 1;
	factor_factorial(n, f, 1);
	factor_factorial(r, f, -1);
	factor_factorial(n - r, f, -1);
	for(auto & pot : f){
		ans *= pow(pot.first, pot.second);
		if(pot.second > 1) return 0;
	}
	return ans;
}

int main(){
	criba(51);
	lli sum = 0;
	lli n = 50;
	map<lli, int> distinct;
	for(lli i = 0; i <= n; i++){
		for(lli j = 0; j <= i; j++){
			lli tmp = squareFree(i, j);
			if(tmp != 0 && distinct[tmp] == 0){
				sum += tmp;
				distinct[tmp]++;
			}
		}
	}
	cout << sum << "\n";
	return 0;
}