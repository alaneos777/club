#include <bits/stdc++.h>

using namespace std;

typedef long long int ull;

void criba_divisores(ull n, vector<int> & v){
	for(ull i = 1; i <= n; i++){
		for(ull j = i; j <= n; j += i){
			v[j]++;
		}
	}
}

int main(){
	ull n, ans = 0;
	cin >> n;
	vector<int> numero_divisores(n + 1, 0);
	criba_divisores(n, numero_divisores);
	for(ull i = 1; i <= n; i++){
		if(numero_divisores[i] == 4) ans++;
	}
	cout << ans;
	return 0;
}