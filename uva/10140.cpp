#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<bool> es_primo;
vector<lli> primos;

void criba(lli n){
	es_primo.resize(n + 1, true);
	es_primo[0] = es_primo[1] = false;
	es_primo[2] = true;
	primos.push_back(2);
	for(lli i = 4; i <= n; i += 2){
		es_primo[i] = false;
	}
	lli limit = sqrt(n);
	for(lli i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(lli j = i * i; j <= n; j += 2 * i){
					es_primo[j] = false;
				}
			}
		}
	}
}

bool primeTest(lli n){
	if(n <= 46341){
		return es_primo[n];
	}else{
		for(lli & p : primos){
			if(p * p > n) break;
			if(n % p == 0) return false;
		}
		return true;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(46341);
	lli l, u;
	while(cin >> l >> u){
		lli minimo = -1, maximo = -1, dist = 0, c1, c2, c3 = -1, d1, d2, d3 = -1;
		while((!primeTest(l)) && l < u){
			++l;
		}
		while((!primeTest(u)) && l < u){
			--u;
		}
		if(l < u){
			c1 = d1 = l;
			lli cont_min = 0, cont_max = 1;
			for(lli i = l + 1; i <= u; i++){
				++cont_min, ++cont_max;
				if(primeTest(i)){
					if(minimo == -1){
						c2 = i;
						minimo = cont_min;
					}else{
						if(cont_min < minimo){
							minimo = cont_min;
							if(c3 == -1){
								c1 = c2;
							}else{
								c1 = c3;
							}
							c2 = i;
							c3 = -1;
						}else{
							c3 = i;
						}
					}
					cont_min = 0;
					if(maximo == -1){
						d2 = i;
						maximo = cont_max;
					}else{
						if(cont_max > maximo){
							maximo = cont_max;
							if(d3 == -1){
								d1 = d2;
							}else{
								d1 = d3;
							}
							d2 = i;
							d3 = -1;
						}else{
							d3 = i;
						}
					}
					cont_max = 0;
				}
			}
			cout << c1 << "," << c2 << " are closest, " << d1 << "," << d2 << " are most distant.\n";
		}else{
			cout << "There are no adjacent primes.\n";
		}
	}
	return 0;
}