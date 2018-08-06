#include <bits/stdc++.h>
using namespace std;

vector<bool> es_primo;
vector<int> primos;

void criba(int n){
	es_primo.resize(n + 1, true);
	primos.push_back(2);
	int limit = sqrt(n);
	for(int i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(int j = i * i; j <= n; j += 2 * i){
					es_primo[j] = false;
				}
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(1e8);
	int x;
	while(cin >> x && x != 0){
		int pi = upper_bound(primos.begin(), primos.end(), x) - primos.begin();
		long double aprox = x / log(x);
		long double error = abs(pi - aprox) / pi * 100;
		cout << fixed << setprecision(1) << error << "\n";
	}
	return 0;
}