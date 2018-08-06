#include <bits/stdc++.h>
using namespace std;

typedef long long int ull;

void criba(ull n, vector<bool> & es_primo){
	ull limit = sqrt(n);
	es_primo.resize(n + 1, true);
	es_primo[0] = es_primo[1] = false;
	for(ull i = 2; i <= limit; ++i){
		while(!es_primo[i]) ++i;
		for(ull j = 2 * i; j <= n; j+=i){
			es_primo[j] = false;
		}
	}
}

int main(){
	vector<bool> es_primo;
	criba(1e9+7, es_primo);
	return 0;
}